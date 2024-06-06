#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/PlatformerSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"
#include "PlayerCharacter.h"

bool UPlatformerGameInstance::SaveGame(UWorld* World, const FString& SlotName, const int32 UserIndex)
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
				UGameplayStatics::SaveGameToSlot(PlatformerSaveGame, SlotName, UserIndex);

				UE_LOG(LogTemp, Warning, TEXT("LOAD BEFORE - Location: %s - Rotation: %s - CurrentPoints: %d"), *PlatformerSaveGame->SaveData.CharacterLocation.ToString(), *PlatformerSaveGame->SaveData.CharacterRotation.ToString(), PlatformerSaveGame->SaveData.CurrentPoints);

				// Temp
				UPlatformerSaveGame* LoadedGame = Cast<UPlatformerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
				if (LoadedGame)
				{
					UE_LOG(LogTemp, Warning, TEXT("LOAD AFTER - Location: %s - Rotation: %s - CurrentPoints: %d"), *LoadedGame->SaveData.CharacterLocation.ToString(), *LoadedGame->SaveData.CharacterRotation.ToString(), LoadedGame->SaveData.CurrentPoints);
				}

				return true;
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
				Character->SetActorRotation(PlatformerSaveGame->SaveData.CharacterRotation);
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