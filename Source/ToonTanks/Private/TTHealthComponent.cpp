// Fill out your copyright notice in the Description page of Project Settings.


#include "TTHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TTGameMode.h"

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

void UTTHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = NewHealth;
}

void UTTHealthComponent::AddHealth(float AmtToAdd)
{
	CurrentHealth += AmtToAdd;
	FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
	if (CurrentHealth <= 0.f)
	{
		DeathDel.Broadcast(GetOwner());
		ATTGameMode* GM = Cast<ATTGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			UE_LOG(LogTemp, Warning, TEXT("Game mode valid"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Game mode NOT valid"));
		}
		//UE_LOG(LogTemp, Warning, TEXT("You killed %s"), *GetOwner()->GetName());
	}
}

// Called when the game starts
void UTTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

