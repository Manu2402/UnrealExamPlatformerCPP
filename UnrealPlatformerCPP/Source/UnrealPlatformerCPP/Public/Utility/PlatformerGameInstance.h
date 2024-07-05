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

	class ACharacter* Character;
	class APlayerCharacterState* PlayerCharacterState;
	class AMainLevelScriptActor* MainLevelScriptActor;

	class UPlatformerSaveGame* PlatformerSaveGame;
	class UBestScoreSaveGame* BestScoreSaveGame;
	class UTubeManagerSubsystem* TubeManager;

	const FString& BestScoreSlotName = TEXT("BestScoreSlot");

public:
	const FName& MainLevelName = TEXT("Main");
	const FName& SlotsLevelName = TEXT("SlotsLevel");

	bool SaveGame(UWorld* World, const FString& SlotName, int32 UserIndex);
	bool LoadGame(UWorld* World, const FString& SlotName, int32 UserIndex);
	bool EndGame(const FString& SlotName, int32 UserIndex);

	bool SaveBestScore(UWorld* World, int32 UserIndex);
	bool LoadBestScore(UWorld* World, int32 UserIndex);

	ESlotsIndex GetCurrentSlotIndex() const;
	void SetCurrentSlotIndex(const ESlotsIndex& SlotIndex);
};