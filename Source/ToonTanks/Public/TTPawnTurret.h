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
public:
	ATTPawnTurret();

private:
	UFUNCTION()
	void CheckFireCondition();

	UFUNCTION()
	void InitializePawnTank();

	UFUNCTION()
	float GetDistanceToPlayer();

	UFUNCTION()
	void AcquireTargetAndRotate();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	FTimerHandle FireRateTimerHandle;

	UPROPERTY()
	FTimerHandle RotateTurretTimerHandle;

	FTimerDelegate RotateTurretTimerDel;

	UPROPERTY()
	class ATTPawnTank* PawnTank;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateToLook(FVector Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretRotRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceThreshold;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
