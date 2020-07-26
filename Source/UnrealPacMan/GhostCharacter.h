// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GhostCharacter.generated.h"

UCLASS()
class UNREALPACMAN_API AGhostCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGhostCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetVulnerability(bool bValue);

	bool IsVulnerable();

	bool IsEaten();

	void SetEaten(bool Value);

	void ChangeColor();

	void GiveTemporalDeathColor();

private:

	bool bIsEaten = false;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GhostMesh;

	UPROPERTY(EditDefaultsOnly)
	float MaxGhostSpeed = 300.0f;

	bool bIsVulnerable;

	UPROPERTY(EditAnywhere)
	class UMaterial* GhostMaterial;

	UPROPERTY(EditDefaultsOnly)
	FColor WeakColor = FColor(0, 0, 255, 255);

	UPROPERTY(EditDefaultsOnly)
	FColor DeathColor = FColor(255, 255, 255, 0);

	UPROPERTY()
	class UMaterialInstanceDynamic* WeakGhostMaterial;

	UPROPERTY()
	class UMaterialInstanceDynamic* DeathGhostMaterial;
	

};
