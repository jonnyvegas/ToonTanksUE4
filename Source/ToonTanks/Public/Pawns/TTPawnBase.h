// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TTPawnBase.generated.h"

UCLASS()
class TOONTANKS_API ATTPawnBase : public APawn
{
	GENERATED_BODY()

private:

		  
public:
	// Sets default values for this pawn's properties
	ATTPawnBase();

	UFUNCTION(BlueprintCallable, Category = "Movement Variables")
	float SetMovementSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Variables")
	float GetMovementSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement Variables")
	float SetRotationSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Variables")
	float GetRotationSpeed();

	UFUNCTION()
	virtual void RotateToLook(FVector Target) {};

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* ProjectileSpawnComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTTPawnMovementComponent* MovementComp;

	UPROPERTY()
	class ATTPlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY()
	FVector TargetLoc;
};
