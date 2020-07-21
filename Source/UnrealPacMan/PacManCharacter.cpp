// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"
#include "GhostCharacter.h"

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
	}
}


