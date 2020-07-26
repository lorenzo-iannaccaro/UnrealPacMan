// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GhostBaseTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API AGhostBaseTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AGhostBaseTriggerBox();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BaseOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
