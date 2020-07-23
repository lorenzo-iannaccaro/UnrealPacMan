// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameCamera.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API AGameCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AGameCamera();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	FVector CameraLocation = FVector(0, 0, 2400);

	UPROPERTY(EditDefaultsOnly)
	FRotator CameraRotation = FRotator(-90, 180, 180);

};
