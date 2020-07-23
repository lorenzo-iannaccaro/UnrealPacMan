// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"

AGameCamera::AGameCamera() {

}

void AGameCamera::BeginPlay() {
	SetActorLocation(CameraLocation);
	SetActorRotation(FQuat(CameraRotation));
}