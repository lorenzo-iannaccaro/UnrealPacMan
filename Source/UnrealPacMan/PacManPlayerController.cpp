// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void APacManPlayerController::BeginPlay() {
	Super::BeginPlay();

	StartLocation = GetPawn()->GetActorLocation();

	UUserWidget* HudWidget = CreateWidget(this, HudClass);
	if (HudWidget != nullptr) {
		HudWidget->AddToViewport();
	}
}

void APacManPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner) {
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenClass);
		if (WinScreenWidget != nullptr) {
			WinScreenWidget->AddToViewport();
		}
	}
	else {
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenClass);
		if (LoseScreenWidget != nullptr) {
			LoseScreenWidget->AddToViewport();
		}
	}

	//GetPawn()->DetachFromControllerPendingDestroy();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, LevelRestartDelay);
}

void APacManPlayerController::ReturnToStartLocation() {
	GetPawn()->SetActorLocation(StartLocation);
}

void APacManPlayerController::PauseGame() {
	UUserWidget* PauseScreenWidget = CreateWidget(this, PauseScreenClass);
	if (PauseScreenWidget != nullptr) {
		PauseScreenWidget->AddToViewport();
	}
	
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	SetPause(true);
}

