// Fill out your copyright notice in the Description page of Project Settings.


#include "EatAllPillsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pill.h"
#include "EngineUtils.h"

void AEatAllPillsGameModeBase::PillEaten(APill* Pill) {
	UE_LOG(LogTemp, Warning, TEXT("Game mode knows that a pill has been eaten"));

	Pill->Destroy();

	TArray<AActor*> PillArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PillClass, PillArray);

	//TActorRange<APill>(GetWorld());

	UE_LOG(LogTemp, Warning, TEXT("Remaining pills: %d"), PillArray.Num());
	if (PillArray.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("All pills have been eaten"));
	}
}