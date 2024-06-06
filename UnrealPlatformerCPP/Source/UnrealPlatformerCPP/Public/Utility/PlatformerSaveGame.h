#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlatformerSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = Basic)
	FVector CharacterLocation;

	UPROPERTY(BlueprintReadWrite, Category = Basic)
	FRotator CharacterRotation;

	UPROPERTY(BlueprintReadWrite, Category = Basic)
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
