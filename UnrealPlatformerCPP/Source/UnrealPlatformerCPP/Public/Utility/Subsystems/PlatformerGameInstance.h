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
class UNREALPLATFORMERCPP_API UPlatformerGameInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:	
	ESlotsIndex CurrentSlotIndex;

public:
	bool SaveGame(UWorld* World, const FString& SlotName, const int32& UserIndex) const;
	bool LoadGame(UWorld* World, const FString& SlotName, const int32& UserIndex) const;

	ESlotsIndex GetCurrentSlotIndex() const;
	void SetCurrentSlotIndex(ESlotsIndex SlotIndex);

	const FName& MainLevelName = TEXT("Main");
	const FName& SlotsLevelName = TEXT("SlotsLevel");
};