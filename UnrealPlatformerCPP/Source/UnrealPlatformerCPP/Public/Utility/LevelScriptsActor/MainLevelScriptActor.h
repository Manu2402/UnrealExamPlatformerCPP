#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	FInputModeGameOnly InputMode = FInputModeGameOnly(); // Not const because i will use it to do a cast.

public:
	virtual void BeginPlay() override;

	void ToggleInputMode();
	void LoadSaves();
};
