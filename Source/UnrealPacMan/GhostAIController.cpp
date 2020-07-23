// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GhostCharacter.h"

void AGhostAIController::BeginPlay() {
	Super::BeginPlay();

	ControlledGhost = Cast<AGhostCharacter>(GetPawn());
	if (ControlledGhost != nullptr) {
		StartLocation = ControlledGhost->GetActorLocation();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cannot possess Ghost"));
	}

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr) {
		SetFocus(PlayerPawn);
	}
}

void AGhostAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (PlayerPawn != nullptr && ControlledGhost != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("Player pawn found"));
		//MoveToActor(PlayerPawn, 0, false);

		if (ControlledGhost->IsVulnerable()) {
			MoveToLocation(StartLocation);
		}
		else {
			MoveToActor(PlayerPawn, 0, false);
		}
	}
}

void AGhostAIController::RandomMove() {

	//FNavLocation RandomDestination;
	
	//UNavigationSystem* Nav = UNavigationSystem::GetCurrent(GetWorld());
	//bool bOk = GetRandomReachablePointInRadius(PlayerPawn->GetActorLocation(), 500, RandomDestination);
}

void AGhostAIController::ReturnToStartLocation() {
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