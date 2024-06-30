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
	
	class TSubclassOf<UUserWidget> ScoreWidgetClass;
	class UScoreWidget* ScoreWidgetInstance;

public:
	virtual void BeginPlay() override;

	void ToggleInputMode();
	void LoadSaves();

	void SetScoreOnUI(int32 Score);
	void SetBestScoreOnUI(int32 Score);
};
