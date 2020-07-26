// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealPacManGameModeBase.h"
#include "EatAllPillsGameModeBase.generated.h"

class AGameCamera;

UCLASS()
class UNREALPACMAN_API AEatAllPillsGameModeBase : public AUnrealPacManGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APill> PillClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameCamera> GameCameraClass;

	UFUNCTION(BlueprintPure)
	int GetRemainingPillsCount();

	virtual void PillEaten(APill* Pill) override;

	virtual void StrenghtenSingleGhost(AGhostCharacter* Ghost) override;

	void PacmanPermadeath();

	void AllGhostsToBase();

protected:
	virtual void BeginPlay() override;

	void SetPacmanGameCamera();

private:
	UPROPERTY()
	TArray<AActor*> GhostsArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGhostCharacter> GhostClass;

	UPROPERTY(EditDefaultsOnly)
	float PowerPillEffectDurationInSeconds = 10.0f;

	FTimerHandle TimerHandle;

	AGameCamera* GameCamera;

	int RemainingPillsCount;

	void GameEnd(bool bIsWin);

	void WeakenGhosts();

	void StrenghtenGhosts();
	
};
