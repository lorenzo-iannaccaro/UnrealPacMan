// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPill.h"
#include "Kismet/GameplayStatics.h"
#include "PacManCharacter.h"

APowerPill::APowerPill() {

}

void APowerPill::BeginPlay() {
	Super::BeginPlay();
}

void APowerPill::PillOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	Super::PillOverlapped(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APacManCharacter* PacmanPlayer = Cast<APacManCharacter>(OtherActor);
	if (PacmanPlayer != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PowerPillEatenSfx, GetActorLocation());

	}
}