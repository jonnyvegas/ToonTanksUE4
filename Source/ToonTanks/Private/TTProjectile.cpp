// Fill out your copyright notice in the Description page of Project Settings.


#include "TTProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATTProjectile::ATTProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 5000.f;

}

// Called when the game starts or when spawned
void ATTProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

