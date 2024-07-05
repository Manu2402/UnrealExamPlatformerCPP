#include "Utility/LevelScriptsActor/SlotsLevelScriptActor.h"
#include "Player/PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SlotsWidget.h"

void ASlotsLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	PlayerCharacterController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(World, 0));
	
	InitSlotsWidget();
}

void ASlotsLevelScriptActor::InitSlotsWidget()
{
	SlotsWidgetClass = LoadClass<USlotsWidget>(nullptr, SlotsWidgetPath);
	SlotsWidgetInstance = CreateWidget<USlotsWidget>(PlayerCharacterController, SlotsWidgetClass);
	if (SlotsWidgetInstance)
	{
		SlotsWidgetInstance->AddToViewport();
	}

	if (!PlayerCharacterController)
	{
		return;
	}
		
	PlayerCharacterController->ToggleInputMode(InputMode);
}