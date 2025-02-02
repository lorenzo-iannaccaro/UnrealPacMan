// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GhostAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API AGhostAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	FVector GetStartLocation();

	void ReturnToStartLocation();

	void MoveToStartLocation();

	void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	APawn* PlayerPawn = nullptr;

	class AGhostCharacter* ControlledGhost = nullptr;

	FVector StartLocation;
};
