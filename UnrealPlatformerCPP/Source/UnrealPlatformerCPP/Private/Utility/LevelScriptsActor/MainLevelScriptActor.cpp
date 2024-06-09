#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	ToggleInputMode();
	LoadSaves();
}

void AMainLevelScriptActor::ToggleInputMode()
{
	APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerCharacterController)
	{
		PlayerCharacterController->ToggleInputMode(InputMode);
	}
}

void AMainLevelScriptActor::LoadSaves()
{
	UPlatformerGameInstance* PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PlatformerGameInstance)
	{
		PlatformerGameInstance->LoadGame(GetWorld(), UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex()), 0);
	}
}