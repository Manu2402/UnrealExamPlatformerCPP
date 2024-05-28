#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterController.h"

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	ToggleInputMode();
}

void AMainLevelScriptActor::ToggleInputMode()
{
	APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerCharacterController)
	{
		PlayerCharacterController->ToggleInputMode(InputMode);
	}
}