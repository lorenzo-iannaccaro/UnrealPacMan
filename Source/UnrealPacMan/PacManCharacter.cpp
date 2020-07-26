// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"
#include "GhostCharacter.h"
#include "EatAllPillsGameModeBase.h"
#include "PacManPlayerController.h"
#include "GhostAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

int APacManCharacter::GetLivesRemaining() {
	return CurrentLives;
}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APacManCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APacManCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("TogglePause"), IE_Pressed, this, &APacManCharacter::TogglePause);

}

void APacManCharacter::MoveUp(float AxisValue) {
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APacManCharacter::MoveRight(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APacManCharacter::TogglePause() {
	PacmanController->PauseGame();
}

void APacManCharacter::PacManOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	GhostOverlapped = Cast<AGhostCharacter>(OtherActor);
	if (GhostOverlapped != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Ghost overlapped into Pacman"));
		if (GhostOverlapped->IsVulnerable()) {

			EatGhost();
		}
		else {
			LoseALife();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pacman overlapped with a non ghost actor"));
	}
}

void APacManCharacter::EatGhost()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EatGhostSfx, GetActorLocation());
	GhostOverlapped->SetEaten(true);
	GhostOverlapped->GiveTemporalDeathColor();

	AGhostAIController* GhostController = Cast<AGhostAIController>(GhostOverlapped->GetController());
	if (GhostController != nullptr) {
		GhostController->MoveToStartLocation();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Ghost controller is nullptr"));
	}
}

void APacManCharacter::LoseALife() {
	AEatAllPillsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AEatAllPillsGameModeBase>();

	CurrentLives--;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LoseLifeSfx, GetActorLocation());
	PacmanController->ReturnToStartLocation();
	GameMode->AllGhostsToBase();

	if (NoLivesRemain()) {
		UE_LOG(LogTemp, Warning, TEXT("Pacman has lost all lives"));

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


