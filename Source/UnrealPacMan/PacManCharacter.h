// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacManCharacter.generated.h"

UCLASS()
class UNREALPACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	int GetLivesRemaining();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	int MaxLives = 3;

	UPROPERTY(VisibleAnywhere)
	int CurrentLives;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PacmanMesh;

	UPROPERTY()
	class AGhostCharacter* GhostOverlapped;

	class APacManPlayerController* PacmanController;

	void MoveUp(float AxisValue);

	void MoveRight(float AxisValue);

	void TogglePause();

	void LoseALife();

	bool NoLivesRemain();

	UFUNCTION()
	void PacManOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
