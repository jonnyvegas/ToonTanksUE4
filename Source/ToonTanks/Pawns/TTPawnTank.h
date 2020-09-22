// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TTPawnBase.h"
#include "TTPawnTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATTPawnTank : public ATTPawnBase
{
	GENERATED_BODY()

public:

	ATTPawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveFwd(float AxisVal);

	UFUNCTION()
	void MoveRight(float AxisVal);

	UFUNCTION()
	void RotateTurret(float AxisVal);

	//UFUNCTION()
	void RotateToLook() override;

	FRotator TurretMeshRot;

private:

	UPROPERTY()
	FVector CurrentDirection;

	UPROPERTY()
	FRotator CurrentRotation;



	UPROPERTY()
	float NewYaw;

	UPROPERTY()
	UWorld* TheWorld;

	UPROPERTY()
	float MouseX;

	UPROPERTY()
	float MouseY;

	UPROPERTY()
	FVector ScreenLoc;

	UPROPERTY()
	FVector ScreenDirection;

	UPROPERTY()
	FVector2D MouseLoc;


protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;
};
