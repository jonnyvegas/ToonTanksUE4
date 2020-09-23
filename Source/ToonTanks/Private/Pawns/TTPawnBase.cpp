// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TTPawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TTPawnMovementComponent.h"
#include "TTProjectile.h"

// Sets default values
ATTPawnBase::ATTPawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnComp = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnComp"));
	ProjectileSpawnComp->SetupAttachment(TurretMesh);

	MovementComp = CreateDefaultSubobject<UTTPawnMovementComponent>(TEXT("PawnMovementComp"));

	TargetLoc = FVector::ZeroVector;

}

float ATTPawnBase::SetMovementSpeed(float NewSpeed)
{
	// Negative speed doesn't make sense at this time.
	if (NewSpeed >= 0.f)
	{
		MovementSpeed = NewSpeed;
	}
	return GetMovementSpeed();
}

float ATTPawnBase::GetMovementSpeed()
{
	return MovementSpeed;
}

float ATTPawnBase::SetRotationSpeed(float NewSpeed)
{
	if (NewSpeed >= 0.f)
	{
		RotationSpeed = NewSpeed;
	}
	return GetRotationSpeed();
}

float ATTPawnBase::GetRotationSpeed()
{
	return RotationSpeed;
}

void ATTPawnBase::Fire()
{
	if (ProjectileClass && GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ATTProjectile>(ProjectileClass, ProjectileSpawnComp->GetComponentTransform(), SpawnParams);
	}
}

