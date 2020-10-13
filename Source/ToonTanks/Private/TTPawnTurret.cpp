// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/TTPawnTank.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "TTProjectile.h"

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

}

void ATTPawnTurret::InitializePawnTank()
{

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
	ATTPawnTank* ThePawnTank = Cast<ATTPawnTank>(OtherActor); 
	
	if (ThePawnTank)
	{
		PawnTank = ThePawnTank;
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATTPawnTurret::Fire, 2.f, true);
		RotateTurretTimerDel = FTimerDelegate::CreateUObject(this, &ATTPawnTurret::RotateToLook, GetActorLocation() - PawnTank->GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(RotateTurretTimerHandle, RotateTurretTimerDel, 0.04f, true);
	}
}

void ATTPawnTurret::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATTPawnTank* ThePawnTank = Cast<ATTPawnTank>(OtherActor);

	if (ThePawnTank)
	{
		PawnTank = ThePawnTank;
		GetWorld()->GetTimerManager().ClearTimer(RotateTurretTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
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

void ATTPawnTurret::Fire()
{
	Super::Fire();
}

void ATTPawnTurret::BeginPlay()
{
	Super::BeginPlay();
	FireRate = 2.f;
	TurretRotRate = 10.f;
	// 500 UU ~ 16.5 ft
	DistanceThreshold = 500.f;

}

void ATTPawnTurret::ReactToDeath(AActor* DeadActor)
{
	Super::ReactToDeath(DeadActor);
}
