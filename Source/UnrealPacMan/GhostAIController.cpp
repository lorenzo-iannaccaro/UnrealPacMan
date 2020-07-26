// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GhostCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AGhostAIController::BeginPlay() {
	Super::BeginPlay();

	ControlledGhost = Cast<AGhostCharacter>(GetPawn());
	if (ControlledGhost != nullptr) {
		StartLocation = ControlledGhost->GetActorLocation();
	}

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (BehaviorTree != nullptr) {
		RunBehaviorTree(BehaviorTree);
	}

}

void AGhostAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (PlayerPawn != nullptr && ControlledGhost != nullptr) {

		if (!ControlledGhost->IsVulnerable()) {
			if (BehaviorTree != nullptr) {
				if (!BrainComponent->IsRunning()) {
					RunBehaviorTree(BehaviorTree);
				}

			}
		}
	}
}

void AGhostAIController::ReturnToStartLocation() {
	
	BrainComponent->StopLogic(TEXT(""));
	ControlledGhost->SetActorLocation(StartLocation);
}

void AGhostAIController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetPawn()->SetActorEnableCollision(false);
	GetPawn()->DetachFromControllerPendingDestroy();
}

FVector AGhostAIController::GetStartLocation() {
	return StartLocation;
}

// Follow the best path to start location
void AGhostAIController::MoveToStartLocation() {
	BrainComponent->StopLogic(TEXT(""));
	MoveTo(StartLocation);
}