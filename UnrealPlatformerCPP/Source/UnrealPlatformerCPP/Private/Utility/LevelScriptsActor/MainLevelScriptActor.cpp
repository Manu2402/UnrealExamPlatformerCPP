#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/ScoreWidget.h"

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
		PlatformerGameInstance->LoadGame(GetWorld(), UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex()), 0);
	}
}

void AMainLevelScriptActor::SetScore(int32 Score)
{
	ScoreWidgetInstance->SetScore(Score);
}
