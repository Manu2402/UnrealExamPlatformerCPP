#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/PlatformerSaveGame.h"
#include "Utility/BestScoreSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"
#include "PlayerCharacter.h"

bool UPlatformerGameInstance::SaveGame(UWorld* World, const FString& SlotName, int32 UserIndex)
{
	PlatformerSaveGame = Cast<UPlatformerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlatformerSaveGame::StaticClass()));
	if (!PlatformerSaveGame)
	{
		return false;
	}

	Character = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (!Character)
	{
		return false;
	}

	PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return false;
	}

	MainLevelScriptActor = Cast<AMainLevelScriptActor>(World->GetCurrentLevel()->GetLevelScriptActor());
	if (!MainLevelScriptActor)
	{
		return false;
	}

	PlatformerSaveGame->SaveData.CharacterLocation = Character->GetActorLocation();
	PlatformerSaveGame->SaveData.CharacterRotation = Character->GetMesh()->GetRelativeRotation();
	PlatformerSaveGame->SaveData.CurrentPoints = PlayerCharacterState->GetCurrentScore();
	PlatformerSaveGame->SaveData.PPWeight = MainLevelScriptActor->GetPPWeight();

	UGameplayStatics::SaveGameToSlot(PlatformerSaveGame, SlotName, UserIndex);
	return true;
}

bool UPlatformerGameInstance::LoadGame(UWorld* World, const FString& SlotName, int32 UserIndex)
{
	PlatformerSaveGame = Cast<UPlatformerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (!PlatformerSaveGame)
	{
		return false;
	}

	Character = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (!Character)
	{
		return false;
	}

	PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return false;
	}

	MainLevelScriptActor = Cast<AMainLevelScriptActor>(World->GetCurrentLevel()->GetLevelScriptActor());
	if (!MainLevelScriptActor)
	{
		return false;
	}

	Character->SetActorLocation(PlatformerSaveGame->SaveData.CharacterLocation);
	Character->GetMesh()->SetRelativeRotation(PlatformerSaveGame->SaveData.CharacterRotation);
	PlayerCharacterState->SetCurrentScore(PlatformerSaveGame->SaveData.CurrentPoints);
	MainLevelScriptActor->SetPPWeight(PlatformerSaveGame->SaveData.PPWeight);

	return true;
}

bool UPlatformerGameInstance::EndGame(const FString& SlotName, int32 UserIndex)
{
	UGameplayStatics::OpenLevel(GetWorld(), SlotsLevelName);
	return UGameplayStatics::DeleteGameInSlot(SlotName, UserIndex);
}

bool UPlatformerGameInstance::SaveBestScore(UWorld* World, int32 UserIndex)
{
	BestScoreSaveGame = Cast<UBestScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UBestScoreSaveGame::StaticClass()));
	if (!BestScoreSaveGame)
	{
		return false;
	}

	PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return false;
	}

	BestScoreSaveGame->BestScore = PlayerCharacterState->GetBestScore();
	UGameplayStatics::SaveGameToSlot(BestScoreSaveGame, BestScoreSlotName, UserIndex);

	return true;
}

bool UPlatformerGameInstance::LoadBestScore(UWorld* World, int32 UserIndex)
{
	BestScoreSaveGame = Cast<UBestScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(BestScoreSlotName, UserIndex));
	if (!BestScoreSaveGame)
	{
		return false;
	}

	PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return false;
	}

	MainLevelScriptActor = Cast<AMainLevelScriptActor>(World->GetCurrentLevel()->GetLevelScriptActor());
	if (!MainLevelScriptActor)
	{
		return false;
	}

	PlayerCharacterState->SetBestScore(BestScoreSaveGame->BestScore);
	MainLevelScriptActor->SetBestScoreOnUI(PlayerCharacterState->GetBestScore());

	return true;
}

ESlotsIndex UPlatformerGameInstance::GetCurrentSlotIndex() const
{
	return CurrentSlotIndex;
}

void UPlatformerGameInstance::SetCurrentSlotIndex(const ESlotsIndex& SlotIndex)
{
	CurrentSlotIndex = SlotIndex;
}