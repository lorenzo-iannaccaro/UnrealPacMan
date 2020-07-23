// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PacManPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API APacManPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void ReturnToStartLocation();

	void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	float LevelRestartDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	FTimerHandle TimerHandle;

	FVector StartLocation;
	
};
