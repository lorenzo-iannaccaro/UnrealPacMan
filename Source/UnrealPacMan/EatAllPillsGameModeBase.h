// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealPacManGameModeBase.h"
#include "EatAllPillsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API AEatAllPillsGameModeBase : public AUnrealPacManGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PillEaten(APill* Pill) override;

	void PacmanPermadeath();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APill> PillClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGhostCharacter> GhostClass;

private:

	void GameEnd(bool bIsWin);

	void WeakenGhosts();

	void StrenghtenGhosts();

	FTimerHandle TimerHandle;
	
};
