// Fill out your copyright notice in the Description page of Project Settings.

#include "Pill.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PacManCharacter.h"
#include "UnrealPacManGameModeBase.h"

// Sets default values
APill::APill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Pill Root");
	SetRootComponent(Root);

	PillMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pill Body");
	PillMesh->SetupAttachment(Root);

	

}

// Called when the game starts or when spawned
void APill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PillMesh->OnComponentBeginOverlap.AddDynamic(this, &APill::PillOverlapped);
}

void APill::PillOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	UE_LOG(LogTemp, Warning, TEXT("Pill overlapped"));

	APacManCharacter* PacmanPlayer = Cast<APacManCharacter>(OtherActor);
	if (PacmanPlayer != nullptr)
	{
		AUnrealPacManGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AUnrealPacManGameModeBase>();
		if (GameMode != nullptr) {
			GameMode->PillEaten(this);
		}

	}
}

