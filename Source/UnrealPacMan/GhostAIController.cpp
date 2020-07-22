// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAIController.h"
#include "Kismet/GameplayStatics.h"

void AGhostAIController::BeginPlay() {
	Super::BeginPlay();

	StartLocation = GetPawn()->GetActorLocation();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr) {
		SetFocus(PlayerPawn);
	}
}

void AGhostAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (PlayerPawn != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("Player pawn found"));
		MoveToActor(PlayerPawn, 0, false);
	}
}