// Fill out your copyright notice in the Description page of Project Settings.


#include "EatAllPillsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pill.h"
#include "PowerPill.h"
#include "EngineUtils.h"
#include "GhostCharacter.h"
#include "GhostAIController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraActor.h"
#include "GameCamera.h"

void AEatAllPillsGameModeBase::BeginPlay() {
	Super::BeginPlay();

	SetPacmanGameCamera();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GhostClass, GhostsArray);

	TArray<AActor*> PillArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PillClass, PillArray);
	RemainingPillsCount = PillArray.Num();
}

void AEatAllPillsGameModeBase::SetPacmanGameCamera()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	GameCamera = Cast<AGameCamera>(GetWorld()->SpawnActor(GameCameraClass));
	if (OurPlayerController != nullptr && GameCamera != nullptr) {
		OurPlayerController->SetViewTargetWithBlend(GameCamera);
		UE_LOG(LogTemp, Warning, TEXT("Game camera set"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cannot set game camera"));
	}
}

void AEatAllPillsGameModeBase::PillEaten(APill* Pill) {
	UE_LOG(LogTemp, Warning, TEXT("Game mode knows that a pill has been eaten"));

	RemainingPillsCount--;

	// Controllare se la pillola è speciale
	APowerPill* PillExamined = Cast<APowerPill>(Pill);
	if (PillExamined != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("POWER PILL EATEN"));

		// Effetti della pillola speciale - settare timer - ripristinare effetti a timer finito
		WeakenGhosts();
		
	}

	Pill->Destroy();

	if (GetRemainingPillsCount() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("All pills have been eaten"));
		GameEnd(true);
	}
}

void AEatAllPillsGameModeBase::GameEnd(bool bIsWin) {
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		if (Controller->IsPlayerController() && bIsWin) {
			Controller->GameHasEnded(GameCamera, true);
		}
		else if (Controller->IsPlayerController() && !bIsWin) {
			Controller->GameHasEnded(GameCamera, false);
		}
		else {
			// Every controller that is not the player's
			Controller->GameHasEnded(GameCamera, false);
		}

	}
}

void AEatAllPillsGameModeBase::PacmanPermadeath() {

	GameEnd(false);

}

void AEatAllPillsGameModeBase::WeakenGhosts() {

	for (int i = 0; i < GhostsArray.Num(); i++) {
		if (GhostsArray[i] != nullptr) {
			AGhostCharacter* Ghost = Cast<AGhostCharacter>(GhostsArray[i]);
			if (Ghost != nullptr) {
				Ghost->SetVulnerability(true);
				Ghost->ChangeColor();
			}
		}
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEatAllPillsGameModeBase::StrenghtenGhosts, PowerPillEffectDurationInSeconds, false);

}

void AEatAllPillsGameModeBase::StrenghtenGhosts() {
	for (AActor* Actor : GhostsArray)
	{
		if (Actor != nullptr) {
			AGhostCharacter* Ghost = Cast<AGhostCharacter>(Actor);
			if (Ghost != nullptr) {
				if (!Ghost->IsEaten()) {
					Ghost->SetVulnerability(false);
					Ghost->SetEaten(false);
					Ghost->ChangeColor();
				}
			}
		}
		
	}
	
}

void AEatAllPillsGameModeBase::AllGhostsToBase() {
	for (AActor* Actor : GhostsArray)
	{
		AGhostCharacter* Ghost = Cast<AGhostCharacter>(Actor);
		if (Ghost != nullptr) {
			Ghost->SetEaten(false);
			AGhostAIController* GhostController = Cast<AGhostAIController>(Ghost->GetController());
			if (GhostController != nullptr) {
				GhostController->ReturnToStartLocation();
			}
		}
	}
}

int AEatAllPillsGameModeBase::GetRemainingPillsCount() {
	return RemainingPillsCount;
}

void AEatAllPillsGameModeBase::StrenghtenSingleGhost(AGhostCharacter* Ghost) {
	if (Ghost != nullptr) {
		Ghost->SetVulnerability(false);
		Ghost->SetEaten(false);
		Ghost->ChangeColor();
	}
}