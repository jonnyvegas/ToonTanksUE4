// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Function to get the widget to display. Returns bool because otherwise it goes into the Event Graph and not in the list of functions.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool CreateEndGameWidgetAndShow(bool bWon);
	
};
