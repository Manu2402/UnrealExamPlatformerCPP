#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/PlatformerSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"
#include "PlayerCharacter.h"

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
					PlatformerSaveGame->SaveData.CurrentPoints = PlayerCharacterState->GetCurrentPoints();
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
				PlayerCharacterState->SetCurrentPoints(PlatformerSaveGame->SaveData.CurrentPoints);

				return true;
			}
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