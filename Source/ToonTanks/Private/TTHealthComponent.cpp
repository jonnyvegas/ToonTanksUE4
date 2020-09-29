// Fill out your copyright notice in the Description page of Project Settings.


#include "TTHealthComponent.h"

// Sets default values for this component's properties
UTTHealthComponent::UTTHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	MaxHealth = 100.f;
	CurrentHealth = 100.f;
}


void UTTHealthComponent::ResetHealth()
{
	CurrentHealth = 100.f;
}

bool UTTHealthComponent::GetIsDead()
{
	return CurrentHealth <= 0.f;
}

// Called when the game starts
void UTTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

