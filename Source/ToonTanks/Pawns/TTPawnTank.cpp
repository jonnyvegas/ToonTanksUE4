// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Pawns/TTPawnBase.h"
#include "Components/CapsuleComponent.h"


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
	if (GetWorld())
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * AxisVal * MovementSpeed), GetWorld()->GetDeltaSeconds(), MovementSpeed));
	}
}

void ATTPawnTank::MoveRight(float AxisVal)
{
//	AddMovementInput(GetActorRightVector(), AxisVal);
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

void ATTPawnTank::BeginPlay()
{
	Super::BeginPlay();
}
