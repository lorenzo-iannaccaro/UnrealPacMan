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

	// Controllare se la pillola è speciale
	APowerPill* PillExamined = Cast<APowerPill>(Pill);
	if (PillExamined != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("POWER PILL EATEN"));
		// Effetti della pillola speciale - settare timer - ripristinare effetti a timer finito
		WeakenGhosts();
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEatAllPillsGameModeBase::StrenghtenGhosts, PowerPillEffectDurationInSeconds, false);
		
	}

	Pill->Destroy();

	TArray<AActor*> PillArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PillClass, PillArray);

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

	UWorld* GameWorld = GetWorld();
	if (GameWorld != nullptr) {
		for (AGhostAIController* GhostController : TActorRange<AGhostAIController>(GetWorld())) {
			if (GhostController != nullptr) {
				AGhostCharacter* Ghost = Cast<AGhostCharacter>(GhostController->GetPawn());
				if (Ghost != nullptr) {
					Ghost->SetVulnerability(true);
					Ghost->ChangeColor();
				}

			}
		}
	}

}

void AEatAllPillsGameModeBase::StrenghtenGhosts() {

	UWorld* GameWorld = GetWorld();
	if (GameWorld != nullptr) {
		for (AGhostAIController* GhostController : TActorRange<AGhostAIController>(GetWorld())) {
			if (GhostController != nullptr) {
				AGhostCharacter* Ghost = Cast<AGhostCharacter>(GhostController->GetPawn());
				if (Ghost != nullptr) {
					Ghost->SetVulnerability(false);
					Ghost->ChangeColor();
				}

			}
		}
	}
	
}