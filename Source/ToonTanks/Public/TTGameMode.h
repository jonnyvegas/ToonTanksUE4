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
	UFUNCTION(BlueprintImplementableEvent)
	void PawnDied(bool bPlayerPawn);

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> TurretClass;
};
