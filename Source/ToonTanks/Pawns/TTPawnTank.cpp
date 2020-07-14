// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATTPawnTank::ATTPawnTank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(BaseMesh);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATTPawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATTPawnTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATTPawnTank::BeginPlay()
{
	Super::BeginPlay();
}
