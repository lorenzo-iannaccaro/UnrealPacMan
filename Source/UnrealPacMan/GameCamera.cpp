// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"

AGameCamera::AGameCamera() {

}

void AGameCamera::BeginPlay() {
	SetActorLocation(FVector(0, 0, 2400));
	SetActorRotation(FQuat(FRotator(-90, 180, 180)));
}