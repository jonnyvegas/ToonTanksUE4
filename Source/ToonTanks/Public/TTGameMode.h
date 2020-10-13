// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATTGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ATTGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void PawnDied(bool bPlayerPawn);

	UFUNCTION()
	int32 GetNumEnemies();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> TurretClass;


private:

	UPROPERTY()
	int32 NumEnemies;
};
