#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Tube.h"
#include "PlatformerSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector CharacterLocation;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FRotator CharacterRotation;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 CurrentPoints;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	float PPWeight;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TMap<ATube*, bool> TubesState;
};

UCLASS()
class UNREALPLATFORMERCPP_API UPlatformerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPlatformerSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FSaveData SaveData;
};
