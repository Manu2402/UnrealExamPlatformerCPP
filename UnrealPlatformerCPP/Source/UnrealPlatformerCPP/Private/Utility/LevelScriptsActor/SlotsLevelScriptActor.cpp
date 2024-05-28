#include "Utility/LevelScriptsActor/SlotsLevelScriptActor.h"
#include "Widgets/SlotsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterController.h"

void ASlotsLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	InitSlotsWidget();
}

void ASlotsLevelScriptActor::InitSlotsWidget()
{
	SlotsWidgetClass = LoadClass<USlotsWidget>(nullptr, TEXT("/Game/Custom/Widgets/WBP_SlotsWidget.WBP_SlotsWidget_C"));
	SlotsWidgetInstance = CreateWidget<USlotsWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SlotsWidgetClass);
	if (SlotsWidgetInstance)
	{
		SlotsWidgetInstance->AddToViewport();
	}

	APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerCharacterController)
	{
		PlayerCharacterController->ToggleInputMode(InputMode);
	}
}