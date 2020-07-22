// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"
#include "GhostCharacter.h"
#include "EatAllPillsGameModeBase.h"
#include "PacManPlayerController.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PacmanMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pacman Body");
	PacmanMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	PacmanController = Cast<APacManPlayerController>(GetController());
	if (PacmanController == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Cannot find pacman controller"));
	}

	CurrentLives = MaxLives;

	PacmanMesh->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::PacManOverlapped);
	
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APacManCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APacManCharacter::MoveRight);

}

void APacManCharacter::MoveUp(float AxisValue) {
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APacManCharacter::MoveRight(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APacManCharacter::PacManOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	AGhostCharacter* Ghost = Cast<AGhostCharacter>(OtherActor);
	if (Ghost != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Ghost overlapped into Pacman"));

		LoseALife();
	}
}

void APacManCharacter::LoseALife() {
	CurrentLives--;
	PacmanController->ReturnToStartLocation();

	if (NoLivesRemain()) {
		UE_LOG(LogTemp, Warning, TEXT("Pacman has lost all lives"));

		// TODO: inserire detachment e deathcamera

		AEatAllPillsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AEatAllPillsGameModeBase>();
		if (GameMode != nullptr) {
			GameMode->PacmanPermadeath();
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Gamemode not found"));
		}
	}
}

bool APacManCharacter::NoLivesRemain() {
	return CurrentLives <= 0;
}
