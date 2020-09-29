// Fill out your copyright notice in the Description page of Project Settings.


#include "TTProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATTProjectile::ATTProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMeshComp;
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	MovementSpeed = 1300.f;
	ProjectileMovementComp->InitialSpeed = MovementSpeed;
	ProjectileMovementComp->MaxSpeed = MovementSpeed;

	InitialLifeSpan = 3.f;

	DamageAmount = 50.f;
	ProjectileMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ATTProjectile::MeshBeginOverlap);
}

// Called when the game starts or when spawned
void ATTProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATTProjectile::MeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, nullptr, GetOwner(), DmgType);
		this->Destroy();
		// Spawn effects if we hit something. Otherwise just hit the ground and nothing happens, kill it.
	}
}

