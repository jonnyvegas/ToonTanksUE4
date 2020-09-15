// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/TTPawnTank.h"

void ATTPawnTurret::CheckFireCondition()
{
	// Player must be valid and not dead.
	if (PawnTank /*&&  !PawnTank->GetIsDead()*/&& GetDistanceToPlayer() <= DistanceThreshold)
	{

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

float ATTPawnTurret::GetDistanceToPlayer()
{
	if (PawnTank)
	{
		return FVector::Dist(PawnTank->GetActorLocation(), this->GetActorLocation());
	}
	// PawnTank was not valid. Boo.
	return -1.f;
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
	// 500 UU ~ 16.5 ft
	DistanceThreshold = 500.f;
// 	if (GetWorld())
// 	{
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATTPawnTurret::CheckFireCondition, FireRate, true);
	//}
}
