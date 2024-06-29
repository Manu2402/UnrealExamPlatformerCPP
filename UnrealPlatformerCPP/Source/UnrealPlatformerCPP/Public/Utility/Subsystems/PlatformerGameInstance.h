#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlatformerGameInstance.generated.h"

UENUM()
enum ESlotsIndex : uint8
{
	Zero,
	One,
	Two
};

UCLASS()
class UNREALPLATFORMERCPP_API UPlatformerGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:	
	ESlotsIndex CurrentSlotIndex;

public:
	const FName& MainLevelName = TEXT("Main");
	const FName& SlotsLevelName = TEXT("SlotsLevel");

	bool SaveGame(UWorld* World, const FString& SlotName, const int32 UserIndex);
	bool LoadGame(UWorld* World, const FString& SlotName, const int32 UserIndex);
	bool LoseGame(const FString& SlotName, const int32 UserIndex);

	ESlotsIndex GetCurrentSlotIndex() const;
	void SetCurrentSlotIndex(ESlotsIndex SlotIndex);
};