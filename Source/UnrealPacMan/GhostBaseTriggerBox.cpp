// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostBaseTriggerBox.h"
#include "Components/ShapeComponent.h"
#include "GhostCharacter.h"
#include "UnrealPacManGameModeBase.h"

AGhostBaseTriggerBox::AGhostBaseTriggerBox() {

}

// Called when the game starts or when spawned
void AGhostBaseTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGhostBaseTriggerBox::BaseOverlapped);

}

void AGhostBaseTriggerBox::BaseOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	AGhostCharacter* Ghost = Cast<AGhostCharacter>(OtherActor);
	if (Ghost != nullptr)
	{
		AUnrealPacManGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AUnrealPacManGameModeBase>();
		if (GameMode != nullptr) {
			GameMode->StrenghtenSingleGhost(Ghost);
		}

	}

}