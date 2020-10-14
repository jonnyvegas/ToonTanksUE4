// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTTDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UTTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTHealthComponent();


	UFUNCTION()
	void ResetHealth();

	UFUNCTION(BlueprintCallable)
	bool GetIsDead();

	void SetHealth(float NewHealth);

	/**
	* Adds health to the player component.
	* Subtracts health if the value is negative.
	* @param	  AmtToAdd - How much health to add/remove
	*/

	UFUNCTION()
	void AddOrRemoveHealth(float AmtToAdd);

	FTTDeathDelegate DeathDel;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth;

private:
	
	class ATTPawnBase* TTPawn;
		
};
