#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/PlatformerSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"
#include "PlayerCharacter.h"

bool UPlatformerGameInstance::SaveGame(UWorld* World, const FString& SlotName, const int32& UserIndex) const
{
	UPlatformerSaveGame* PlatformerSaveGame = Cast<UPlatformerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlatformerSaveGame::StaticClass()));
	if (PlatformerSaveGame)
	{
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
		if (Character)
		{
			APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
			if (PlayerCharacterState)
			{ 
				PlatformerSaveGame->SaveData.CharacterLocation = Character->GetActorLocation();
				PlatformerSaveGame->SaveData.CharacterRotation = Character->GetActorRotation();
				PlatformerSaveGame->SaveData.CurrentPoints = PlayerCharacterState->GetCurrentPoints();

				UGameplayStatics::SaveGameToSlot(PlatformerSaveGame, SlotName, 0);
				return true;
			}
		}
	}
	return false;
}

bool UPlatformerGameInstance::LoadGame(UWorld* World, const FString& SlotName, const int32& UserIndex) const
{
	UPlatformerSaveGame* LoadGame = Cast<UPlatformerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (LoadGame)
	{
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
		if (Character)
		{
			APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
			if (PlayerCharacterState)
			{
				Character->SetActorLocation(LoadGame->SaveData.CharacterLocation);
				Character->SetActorRotation(LoadGame->SaveData.CharacterRotation);
				PlayerCharacterState->SetCurrentPoints(LoadGame->SaveData.CurrentPoints);

				return true;
			}
		}
	}
	return false;
}

ESlotsIndex UPlatformerGameInstance::GetCurrentSlotIndex() const
{
	UPlatformerSaveGame* PlatformerSaveGame = Cast<UPlatformerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlatformerSaveGame::StaticClass()));
	UE_LOG(LogTemp, Warning, TEXT("CharacterLocation: %s, CharacterRotation: %s, CurrentPoints: %d"), *PlatformerSaveGame->SaveData.CharacterLocation.ToString(), *PlatformerSaveGame->SaveData.CharacterRotation.ToString(), PlatformerSaveGame->SaveData.CurrentPoints);
	return CurrentSlotIndex;
}

void UPlatformerGameInstance::SetCurrentSlotIndex(ESlotsIndex SlotIndex)
{
	CurrentSlotIndex = SlotIndex;
}