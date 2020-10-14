// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TTPawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TTPawnMovementComponent.h"
#include "TTProjectile.h"
#include "TTHealthComponent.h"
#include "Kismet/GameplayStatics.h"

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

	HealthComp = CreateDefaultSubobject<UTTHealthComponent>(TEXT("HealthComp"));

	TargetLoc = FVector::ZeroVector;

	this->OnTakeAnyDamage.AddDynamic(this, &ATTPawnBase::PawnTakeDamage);

	this->HealthComp->DeathDel.AddDynamic(this, &ATTPawnBase::HandleDeath);

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
		SpawnParams.Owner = this;
		// TODO: Spawn actor deferred, set owner, then finish spawning.
		GetWorld()->SpawnActor<ATTProjectile>(ProjectileClass, ProjectileSpawnComp->GetComponentTransform(), SpawnParams);
	}
}

void ATTPawnBase::PawnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	ATTPawnBase* PawnBase = Cast<ATTPawnBase>(DamagedActor);
	if (PawnBase)
	{
		PawnBase->HealthComp->AddOrRemoveHealth(-1 * Damage);
		HandleDamage();
	}
}

void ATTPawnBase::HandleDeath()
{
	// Explode
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorTransform());
	}
	// Set lifetime before removal
	this->Destroy();
	// Get the UI to react to our death depending on who we are (send our actor to the GameMode).
}

