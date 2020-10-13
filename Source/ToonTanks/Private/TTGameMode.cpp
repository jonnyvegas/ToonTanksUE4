// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameMode.h"
#include "Kismet/GameplayStatics.h"


ATTGameMode::ATTGameMode()
{
	NumEnemies = 0;
}

void ATTGameMode::StartPlay()
{
	Super::StartPlay();
	TArray<AActor*> TurretActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TurretClass, TurretActorArray);
	//UE_LOG(LogTemp, Warning, TEXT("Num turrets: %d"), TurretActorArray.Num());
	NumEnemies = TurretActorArray.Num();
}

int32 ATTGameMode::GetNumEnemies()
{
	return NumEnemies;
}
