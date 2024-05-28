#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SlotsLevelScriptActor.generated.h"

/* ALevelScriptActor is the base class about level blueprints. */
UCLASS()
class UNREALPLATFORMERCPP_API ASlotsLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	FInputModeUIOnly InputMode = FInputModeUIOnly(); // Not const because i will use it to do a cast.

public:
	virtual void BeginPlay() override;

	class TSubclassOf<UUserWidget> SlotsWidgetClass;
	class USlotsWidget* SlotsWidgetInstance;

	void InitSlotsWidget();
};
