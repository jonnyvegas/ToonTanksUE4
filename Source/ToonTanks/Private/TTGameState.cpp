// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameState.h"
#include "Kismet/GameplayStatics.h"
#include "TTGameMode.h"

ATTGameState::ATTGameState()
{
	NumDeadBots = 0;
	GameMode = Cast<ATTGameMode>(UGameplayStatics::GetGameMode(this));
}

int32 ATTGameState::GetNumBotsDead()
{
	return NumDeadBots;
}

void ATTGameState::IncreaseDeadBotCount()
{
	NumDeadBots++;
}

void ATTGameState::CheckIfAllBotsDead()
{
	if (GameMode && NumDeadBots == GameMode->GetNumEnemies())
	{
		// Game mode... stop the game. Show a widget to the player that they killed everyone. Victory!
	}
}
