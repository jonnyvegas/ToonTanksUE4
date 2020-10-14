// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TTGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATTGameState : public AGameState
{
	GENERATED_BODY()
public:
	ATTGameState();

	int32 GetNumBotsDead();

	void IncreaseDeadBotCount();

	void CheckIfAllBotsDead();

private:
	
	int32 NumDeadBots;

	class ATTGameMode* GameMode;
};
