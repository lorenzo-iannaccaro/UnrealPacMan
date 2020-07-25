// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealPacManGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPACMAN_API AUnrealPacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PillEaten(class APill* Pill);

	virtual void StrenghtenSingleGhost(class AGhostCharacter* Ghost);
};
