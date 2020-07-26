// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pill.h"
#include "PowerPill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API APowerPill : public APill
{
	GENERATED_BODY()

public:
	APowerPill();

protected:
	virtual void BeginPlay() override;

	virtual void PillOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	USoundBase* PowerPillEatenSfx;

};
