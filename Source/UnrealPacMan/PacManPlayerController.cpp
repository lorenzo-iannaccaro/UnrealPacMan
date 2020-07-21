// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void APacManPlayerController::BeginPlay() {
	Super::BeginPlay();
}

void APacManPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner) {
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenClass);
		if (WinScreenWidget != nullptr) {
			WinScreenWidget->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, LevelRestartDelay);
}

