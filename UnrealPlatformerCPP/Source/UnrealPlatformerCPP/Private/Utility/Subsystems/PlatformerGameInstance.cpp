#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/PlatformerSaveGame.h"
#include "Utility/BestScoreSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"
#include "PlayerCharacter.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"

bool UPlatformerGameInstance::SaveGame(UWorld* World, const FString& SlotName, const int32 UserIndex)
{
	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UPlatformerSaveGame::StaticClass());
	if (SaveGame)
	{
		UPlatformerSaveGame* PlatformerSaveGame = Cast<UPlatformerSaveGame>(SaveGame);
		if (PlatformerSaveGame)
		{
			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
			if (Character)
			{
				APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
				if (PlayerCharacterState)
				{
					PlatformerSaveGame->SaveData.CharacterLocation = Character->GetActorLocation();
					PlatformerSaveGame->SaveData.CharacterRotation = Character->GetMesh()->GetRelativeRotation();
					PlatformerSaveGame->SaveData.CurrentPoints = PlayerCharacterState->GetCurrentScore();
					UGameplayStatics::SaveGameToSlot(PlatformerSaveGame, SlotName, UserIndex);

					return true;
				}
			}
		}
	}
	return false;
}

bool UPlatformerGameInstance::LoadGame(UWorld* World, const FString& SlotName, const int32 UserIndex)
{
	UPlatformerSaveGame* PlatformerSaveGame = Cast<UPlatformerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (PlatformerSaveGame)
	{
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
		if (Character)
		{
			APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
			if (PlayerCharacterState)
			{
				Character->SetActorLocation(PlatformerSaveGame->SaveData.CharacterLocation);
				Character->GetMesh()->SetRelativeRotation(PlatformerSaveGame->SaveData.CharacterRotation);
				PlayerCharacterState->SetCurrentScore(PlatformerSaveGame->SaveData.CurrentPoints);

				return true;
			}
		}
	}
	return false;
}

bool UPlatformerGameInstance::EndGame(const FString& SlotName, const int32 UserIndex)
{
	UGameplayStatics::OpenLevel(GetWorld(), SlotsLevelName);
	return UGameplayStatics::DeleteGameInSlot(SlotName, UserIndex);
}

bool UPlatformerGameInstance::SaveBestScore(UWorld* World, const int32& UserIndex)
{
	UBestScoreSaveGame* BestScoreSaveGame = Cast<UBestScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UBestScoreSaveGame::StaticClass()));
	if (BestScoreSaveGame)
	{
		APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
		if (PlayerCharacterState)
		{
			BestScoreSaveGame->BestScore = PlayerCharacterState->GetBestScore();
			UGameplayStatics::SaveGameToSlot(BestScoreSaveGame, BestScoreSlotName, UserIndex);

			return true;
		}
	}

	return false;
}

bool UPlatformerGameInstance::LoadBestScore(UWorld* World, const int32& UserIndex)
{
	UBestScoreSaveGame* BestScoreSaveGame = Cast<UBestScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(BestScoreSlotName, 0));
	if (BestScoreSaveGame)
	{
		APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
		if (PlayerCharacterState)
		{
			PlayerCharacterState->SetBestScore(BestScoreSaveGame->BestScore);

			return true;
		}
	}

	return false;
}

ESlotsIndex UPlatformerGameInstance::GetCurrentSlotIndex() const
{
	return CurrentSlotIndex;
}

void UPlatformerGameInstance::SetCurrentSlotIndex(ESlotsIndex SlotIndex)
{
	CurrentSlotIndex = SlotIndex;
}