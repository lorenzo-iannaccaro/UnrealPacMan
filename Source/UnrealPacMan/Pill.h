// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pill.generated.h"

UCLASS()
class UNREALPACMAN_API APill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void PillOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PillMesh;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* PillEatenSfx;
	

};
