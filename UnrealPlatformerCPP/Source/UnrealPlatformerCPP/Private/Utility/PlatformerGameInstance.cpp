#include "Utility/PlatformerGameInstance.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/TubeManagerSubsystem.h"
#include "Utility/SaveGames/PlatformerSaveGame.h"
#include "Utility/SaveGames/BestScoreSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacterState.h"
#include "Player/PlayerCharacter.h"
#include "Objects/PlatformEE.h"
#include "AI/Enemy.h"

// This class manage all save systems.

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

	TubeManager = GetSubsystem<UTubeManagerSubsystem>();
	if (!TubeManager)
	{
		return false;
	}

	PlatformerSaveGame->SaveData.CharacterLocation = Character->GetActorLocation();
	PlatformerSaveGame->SaveData.CharacterRotation = Character->GetMesh()->GetRelativeRotation();
	PlatformerSaveGame->SaveData.CurrentPoints = PlayerCharacterState->GetCurrentScore();
	PlatformerSaveGame->SaveData.PPWeight = MainLevelScriptActor->GetPPWeight();
	PlatformerSaveGame->SaveData.TubesState = TubeManager->GetTubesState();

	AEnemy* Enemy = Cast<AEnemy>(UGameplayStatics::GetActorOfClass(World, AEnemy::StaticClass()));
	PlatformerSaveGame->SaveData.bIsEnemyActive = Enemy && Enemy->GetEnemyIsActive();

	APlatformEE* Platform = Cast<APlatformEE>(UGameplayStatics::GetActorOfClass(World, APlatformEE::StaticClass()));
	PlatformerSaveGame->SaveData.bIsPlatformActive = Platform && Platform->GetIsActive();

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

	TubeManager = GetSubsystem<UTubeManagerSubsystem>();
	if (!TubeManager)
	{
		return false;
	}

	Character->SetActorLocation(PlatformerSaveGame->SaveData.CharacterLocation);
	Character->GetMesh()->SetRelativeRotation(PlatformerSaveGame->SaveData.CharacterRotation);

	PlayerCharacterState->SetCurrentScore(PlatformerSaveGame->SaveData.CurrentPoints);
	MainLevelScriptActor->SetScoreOnUI(PlayerCharacterState->GetCurrentScore());

	MainLevelScriptActor->SetPPWeight(PlatformerSaveGame->SaveData.PPWeight);
	TubeManager->SetTubesState(PlatformerSaveGame->SaveData.TubesState);

	AEnemy* Enemy = Cast<AEnemy>(UGameplayStatics::GetActorOfClass(World, AEnemy::StaticClass()));
	if (!Enemy)
	{
		return false;
	}

	Enemy->SetEnemyIsActive(PlatformerSaveGame->SaveData.bIsEnemyActive);

	APlatformEE* Platform = Cast<APlatformEE>(UGameplayStatics::GetActorOfClass(World, APlatformEE::StaticClass()));
	if (!Platform)
	{
		return false;
	}
	
	Platform->SetIsActive(PlatformerSaveGame->SaveData.bIsPlatformActive);

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