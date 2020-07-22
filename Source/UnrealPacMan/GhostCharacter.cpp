// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AGhostCharacter::AGhostCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ghost Body");
	GhostMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AGhostCharacter::BeginPlay()
{
	Super::BeginPlay();

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent != nullptr) {
		MovementComponent->MaxWalkSpeed = MaxGhostSpeed;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cannot set max speed on %s"), *GetName());
	}

	bIsVulnerable = false;

	// Color
	WeakGhostMaterial = UMaterialInstanceDynamic::Create(GhostMesh->GetMaterial(0), NULL);
	WeakGhostMaterial->SetVectorParameterValue(TEXT("Color"), WeakColor);
	
}

// Called every frame
void AGhostCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGhostCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGhostCharacter::SetVulnerability(bool bValue) {
	bIsVulnerable = bValue;
}

bool AGhostCharacter::IsVulnerable() {
	return bIsVulnerable;
}

void AGhostCharacter::ChangeColor() {
	if (IsVulnerable()) {
		GhostMesh->SetMaterial(0, WeakGhostMaterial);
	}
	else {
		GhostMesh->SetMaterial(0, GhostMaterial);
	}
}

