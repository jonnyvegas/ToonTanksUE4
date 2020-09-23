// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Pawns/TTPawnBase.h"
#include "Components/CapsuleComponent.h"
#include "TTPawnMovementComponent.h"
#include "TTPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


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
	RotateToLook(GetTargetLoc());

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
	if (AxisVal != 0 && CapsuleComp && GetWorld())
	{
		CurrentRotation = CapsuleComp->GetComponentRotation();
		NewYaw = CurrentRotation.Yaw + AxisVal * RotationSpeed;
		SetActorRotation(FMath::RInterpTo(CurrentRotation, FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll), GetWorld()->GetDeltaSeconds(), RotationSpeed));

	}
}

void ATTPawnTank::RotateTurret(float AxisVal)
{
	
}

FVector ATTPawnTank::GetTargetLoc()
{
	if (PlayerController)
	{
		if (PlayerController->GetMousePosition(MouseX, MouseY))
		{
			MouseLoc.X = MouseX;
			MouseLoc.Y = MouseY;
			UGameplayStatics::DeprojectScreenToWorld(PlayerController, MouseLoc, WorldLoc, TargetLoc);
		}
	}
	return TargetLoc;
}

void ATTPawnTank::RotateToLook(FVector Target)
{
	TurretMeshRot = TurretMesh->GetComponentRotation(); 
	TurretMeshRot.Yaw = FRotationMatrix::MakeFromX(Target).Rotator().Yaw;
	if (GetWorld())
	{
		TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TurretMeshRot, GetWorld()->GetDeltaSeconds(), RotationSpeed));
	}		
}

void ATTPawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ATTPlayerController>(GetWorld()->GetFirstPlayerController());
	MouseX = -1.f;
	MouseY = -1.f;
	WorldLoc = FVector(FVector::ZeroVector);
	WorldDirection = FVector(FVector::ZeroVector);
	MouseLoc = FVector2D(-1.f, -1.f);
	TurretMeshRot = FRotator(FRotator::ZeroRotator);
}
