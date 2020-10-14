// Fill out your copyright notice in the Description page of Project Settings.


#include "TTHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TTGameMode.h"
#include "../Pawns/TTPawnTank.h"
#include "TTGameState.h"

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

void UTTHealthComponent::AddOrRemoveHealth(float AmtToAdd)
{
	CurrentHealth += AmtToAdd;
	FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
	if (CurrentHealth <= 0.f)
	{
		DeathDel.Broadcast();
		
		ATTPawnTank* PawnTank = Cast<ATTPawnTank>(TTPawn);
		if (PawnTank)
		{
			ATTGameMode* GM = Cast<ATTGameMode>(UGameplayStatics::GetGameMode(this));
			// Pawn died!
			if(GM)
			{
				GM->PawnDied(true);
			}
		}
		else
		{
			// Increase the number of enemies from the game state. Have the game state check the game mode.
			ATTGameState* GS = Cast<ATTGameState>(UGameplayStatics::GetGameState(this));
			if (GS)
			{
				GS->IncreaseDeadBotCount();
				GS->CheckIfAllBotsDead();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Game state not valid"));
			}
		}
		
	}
}

// Called when the game starts
void UTTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TTPawn = Cast<ATTPawnBase>(GetOwner());
}

