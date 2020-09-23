// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/TTPawnTank.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"

ATTPawnTurret::ATTPawnTurret()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSphereRadius(500.f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATTPawnTurret::OnSphereBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ATTPawnTurret::OnSphereEndOverlap);

}

void ATTPawnTurret::CheckFireCondition()
{
	// Player must be valid and not dead.
// 	if (PawnTank /*&&  !PawnTank->GetIsDead()*/&& GetDistanceToPlayer() <= DistanceThreshold && GetWorld())
// 	{
// 		GetWorld()->GetTimerManager().SetTimer(RotateTurretTimerHandle, this, &ATTPawnTurret::RotateToLook, 0.01f, true);
// 	}
// 	// Clear the rotation timer.
// 	else
// 	{
// 		GetWorld()->GetTimerManager().ClearTimer(RotateTurretTimerHandle);
// 		//UE_LOG(LogTemp, Warning, TEXT("Clearing check fire condition timer"));
// 	}

	// Check if the player is in range and if so, fire

}

void ATTPawnTurret::InitializePawnTank()
{
// 	PawnTank = Cast<ATTPawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
// 	if (PawnTank)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Pawn initialized!"));
// 	}
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

void ATTPawnTurret::AcquireTargetAndRotate()
{

}

void ATTPawnTurret::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PawnTank = Cast<ATTPawnTank>(OtherActor);
	
	if (PawnTank)
	{
		RotateTurretTimerDel = FTimerDelegate::CreateUObject(this, &ATTPawnTurret::RotateToLook, GetActorLocation() - PawnTank->GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(RotateTurretTimerHandle, RotateTurretTimerDel, 0.02f, true);
	}
}

void ATTPawnTurret::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PawnTank = Cast<ATTPawnTank>(OtherActor);

	if (PawnTank)
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateTurretTimerHandle);
	}
}

void ATTPawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATTPawnTurret::RotateToLook(FVector Target)
{
	if (PawnTank)
	{
		FRotator TurretRot = FRotationMatrix::MakeFromX(PawnTank->GetActorLocation() - GetActorLocation()).Rotator();
		if (TurretMesh)
		{
			TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TurretRot, GetWorld()->GetDeltaSeconds(), TurretRotRate));
		}
	}
}

void ATTPawnTurret::BeginPlay()
{
	Super::BeginPlay();
	FireRate = 2.f;
	TurretRotRate = 10.f;
	InitializePawnTank();
	// 500 UU ~ 16.5 ft
	DistanceThreshold = 500.f;

	//GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATTPawnTurret::CheckFireCondition, FireRate, true);

}
