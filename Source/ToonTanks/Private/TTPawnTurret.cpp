// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/TTPawnTank.h"

void ATTPawnTurret::CheckFireCondition()
{
	// Player must be valid and not dead.
	if (PawnTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn is valid!~"));
	}

	// Check if the player is in range and if so, fire

}

void ATTPawnTurret::InitializePawnTank()
{
	PawnTank = Cast<ATTPawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PawnTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn initialized!"));
	}
}

void ATTPawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATTPawnTurret::BeginPlay()
{
	Super::BeginPlay();
	FireRate = 2.f;
	InitializePawnTank();
// 	if (GetWorld())
// 	{
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATTPawnTurret::CheckFireCondition, FireRate, true);
	//}
}
