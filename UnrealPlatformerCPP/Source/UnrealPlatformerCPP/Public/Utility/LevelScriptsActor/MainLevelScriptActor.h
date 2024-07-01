#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	const TCHAR* ScoreWidgetPath = TEXT("/Game/Custom/Widgets/WBP_ScoreWidget.WBP_ScoreWidget_C");

	FInputModeGameOnly InputMode = FInputModeGameOnly(); // Not const because i will use it to do a cast.
	
	UWorld* World;

	// Widgets about UI.
	class TSubclassOf<UUserWidget> ScoreWidgetClass;
	class UScoreWidget* ScoreWidgetInstance;

	// References
	class APlayerCharacter* PlayerCharacter;
	class UCameraComponent* CameraComponent;
	class APlayerCharacterController* PlayerCharacterController;
	class UPlatformerGameInstance* PlatformerGameInstance;

	// Weight about "vignette" shader.
	float PPWeight;

public:
	virtual void BeginPlay() override;

	void ToggleInputMode() const;
	void LoadSaves() const;

	void SetScoreOnUI(const int32& Score) const;
	void SetBestScoreOnUI(const int32& Score) const;

	float GetPPWeight() const;
	void SetPPWeight(float Weight);

	void SetPostProcessingEffectByWeight(const float& Weight);

};
