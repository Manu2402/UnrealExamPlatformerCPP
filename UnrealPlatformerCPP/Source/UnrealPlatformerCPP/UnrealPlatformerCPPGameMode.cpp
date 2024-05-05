// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealPlatformerCPPGameMode.h"
#include "UnrealPlatformerCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealPlatformerCPPGameMode::AUnrealPlatformerCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
