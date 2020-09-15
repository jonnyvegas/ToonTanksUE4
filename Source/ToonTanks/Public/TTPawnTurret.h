// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TTPawnBase.h"
#include "TTPawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATTPawnTurret : public ATTPawnBase
{
	GENERATED_BODY()
	
private:

	
	UFUNCTION()
	void CheckFireCondition();

	UFUNCTION()
	void InitializePawnTank();

	FTimerHandle FireRateTimerHandle;

	class ATTPawnTank* PawnTank;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
