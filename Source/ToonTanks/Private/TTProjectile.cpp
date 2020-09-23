// Fill out your copyright notice in the Description page of Project Settings.


#include "TTProjectile.h"

// Sets default values
ATTProjectile::ATTProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));

}

// Called when the game starts or when spawned
void ATTProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

