#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/ScoreWidget.h"
#include "PlayerCharacterState.h"

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	ToggleInputMode();
	LoadSaves();

	ScoreWidgetClass = LoadClass<UScoreWidget>(nullptr, TEXT("/Game/Custom/Widgets/WBP_ScoreWidget.WBP_ScoreWidget_C"));
	ScoreWidgetInstance = CreateWidget<UScoreWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScoreWidgetClass);
	if (ScoreWidgetInstance)
	{
		ScoreWidgetInstance->AddToViewport();
	}
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
		UWorld* World = GetWorld();
		PlatformerGameInstance->LoadGame(World, UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex()), 0);
		PlatformerGameInstance->LoadBestScore(World, 0);
	}
}

void AMainLevelScriptActor::SetScoreOnUI(int32 Score)
{
	ScoreWidgetInstance->SetScore(Score);
}

void AMainLevelScriptActor::SetBestScoreOnUI(int32 Score)
{
	ScoreWidgetInstance->SetBestScore(Score);
}