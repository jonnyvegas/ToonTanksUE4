// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Pawns/TTPawnBase.h"
#include "Components/CapsuleComponent.h"
#include "TTPawnMovementComponent.h"
#include "TTPlayerController.h"
#include "Kismet/GameplayStatics.h"


ATTPawnTank::ATTPawnTank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(BaseMesh);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CurrentDirection = FVector::ZeroVector;

	CurrentRotation = FRotator::ZeroRotator;
	MovementSpeed = 100.f;
	RotationSpeed = 15.f;
	NewYaw = 0.f;
}

void ATTPawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateToLook();

}

void ATTPawnTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveFwd", this, &ATTPawnTank::MoveFwd);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATTPawnTank::MoveRight);
	PlayerInputComponent->BindAxis("RotateTurret", this, &ATTPawnTank::RotateTurret);
}

void ATTPawnTank::MoveFwd(float AxisVal)
{
	if (!TheWorld)
	{
		TheWorld = GetWorld();
	}
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * AxisVal * MovementSpeed), TheWorld->GetDeltaSeconds(), MovementSpeed));
// 	if (MovementComp)
// 	{
// 		AddMovementInput(GetActorForwardVector(), 1000.f);
// 	}
}

void ATTPawnTank::MoveRight(float AxisVal)
{
//	AddMovementInput(GetActorRightVector(), AxisVal);
	RotateTurret(AxisVal);
}

void ATTPawnTank::RotateTurret(float AxisVal)
{
	if (AxisVal != 0 && CapsuleComp && GetWorld())
	{
		CurrentRotation = CapsuleComp->GetComponentRotation();
		NewYaw = CurrentRotation.Yaw + AxisVal * RotationSpeed;
		SetActorRotation(FMath::RInterpTo(CurrentRotation, FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll), GetWorld()->GetDeltaSeconds(), RotationSpeed));
		
	}
}

void ATTPawnTank::RotateToLook()
{
	if (PlayerController)
	{
		if (PlayerController->GetMousePosition(MouseX, MouseY))
		{
			MouseLoc.X = MouseX;
			MouseLoc.Y = MouseY;
			if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, MouseLoc, ScreenLoc, ScreenDirection) && TurretMesh)
			{
				TurretMeshRot = TurretMesh->GetComponentRotation(); 
				TurretMeshRot.Yaw = FRotationMatrix::MakeFromX(ScreenDirection).Rotator().Yaw;
				TurretMesh->SetWorldRotation(TurretMeshRot);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("didn't deproject"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Mouse invalid"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PC Invalid."))
	}
}

void ATTPawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ATTPlayerController>(GetWorld()->GetFirstPlayerController());
	MouseX = -1.f;
	MouseY = -1.f;
	ScreenLoc = FVector(FVector::ZeroVector);
	ScreenDirection = FVector(FVector::ZeroVector);
	MouseLoc = FVector2D(-1.f, -1.f);
	TurretMeshRot = FRotator(FRotator::ZeroRotator);
}
