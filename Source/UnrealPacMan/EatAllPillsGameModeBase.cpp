// Fill out your copyright notice in the Description page of Project Settings.


#include "EatAllPillsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pill.h"
#include "PowerPill.h"
#include "EngineUtils.h"
#include "GhostCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

void AEatAllPillsGameModeBase::PillEaten(APill* Pill) {
	UE_LOG(LogTemp, Warning, TEXT("Game mode knows that a pill has been eaten"));

	// TODO: controllare se la pillola è speciale
	APowerPill* PillExamined = Cast<APowerPill>(Pill);
	if (PillExamined != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("POWER PILL EATEN"));
		// TODO: implementare effetti della pillola speciale - settare timer - ripristinare effetti a timer finito
		WeakenGhosts();
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEatAllPillsGameModeBase::StrenghtenGhosts, 10.0f, false);
		
	}

	Pill->Destroy();

	TArray<AActor*> PillArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PillClass, PillArray);

	//TActorRange<APill>(GetWorld());

	UE_LOG(LogTemp, Warning, TEXT("Remaining pills: %d"), PillArray.Num());
	if (PillArray.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("All pills have been eaten"));
		GameEnd(true);
	}
}

void AEatAllPillsGameModeBase::GameEnd(bool bIsWin) {
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		if (Controller->IsPlayerController() && bIsWin) {
			Controller->GameHasEnded(Controller->GetPawn(), true);
		}
		else if (Controller->IsPlayerController() && !bIsWin) {
			Controller->GameHasEnded(Controller->GetPawn(), false);
		}
	}
}

void AEatAllPillsGameModeBase::PacmanPermadeath() {

	GameEnd(false);

}

void AEatAllPillsGameModeBase::WeakenGhosts() {
	TArray<AActor*> GhostsArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GhostClass, GhostsArray);

	for (AActor* Actor : GhostsArray)
	{
		AGhostCharacter* Ghost = Cast<AGhostCharacter>(Actor);
		if (Ghost != nullptr) {
			Ghost->SetVulnerability(true);
			Ghost->ChangeColor();
		}
	}

}

void AEatAllPillsGameModeBase::StrenghtenGhosts() {
	TArray<AActor*> GhostsArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GhostClass, GhostsArray);

	for (AActor* Actor : GhostsArray)
	{
		AGhostCharacter* Ghost = Cast<AGhostCharacter>(Actor);
		if (Ghost != nullptr) {
			Ghost->SetVulnerability(false);
			Ghost->ChangeColor();
		}
	}

}