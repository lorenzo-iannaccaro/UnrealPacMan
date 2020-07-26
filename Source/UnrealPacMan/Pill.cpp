// Fill out your copyright notice in the Description page of Project Settings.

#include "Pill.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PacManCharacter.h"
#include "UnrealPacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APill::APill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Pill Root");
	SetRootComponent(Root);

	PillMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pill Body");
	PillMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void APill::BeginPlay()
{
	Super::BeginPlay();

	PillMesh->OnComponentBeginOverlap.AddDynamic(this, &APill::PillOverlapped);
	
}

void APill::PillOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	APacManCharacter* PacmanPlayer = Cast<APacManCharacter>(OtherActor);
	if (PacmanPlayer != nullptr)
	{
		AUnrealPacManGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AUnrealPacManGameModeBase>();
		if (GameMode != nullptr) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PillEatenSfx, GetActorLocation());
			GameMode->PillEaten(this);
		}

	}
}

