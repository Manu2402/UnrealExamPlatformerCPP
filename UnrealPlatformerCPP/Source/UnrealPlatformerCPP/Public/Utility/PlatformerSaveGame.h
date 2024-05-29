#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlatformerSaveGame.generated.h"

USTRUCT()
struct FSaveData
{
	GENERATED_BODY()

	FVector CharacterLocation;
	FRotator CharacterRotation;
	int32 CurrentPoints;
};

UCLASS()
class UNREALPLATFORMERCPP_API UPlatformerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPlatformerSaveGame();

	FSaveData SaveData;
};
