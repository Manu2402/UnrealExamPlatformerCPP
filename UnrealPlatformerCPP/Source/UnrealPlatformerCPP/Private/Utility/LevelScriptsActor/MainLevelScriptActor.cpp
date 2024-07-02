#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/Subsystems/TubeManagerSubsystem.h"
#include "PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Widgets/ScoreWidget.h"
#include "PlayerCharacter.h"

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	PlayerCharacterController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(World, 0));
	
	PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(World));

	ToggleInputMode();

	// Getting reference about widget blueprint class, and with this i'm creating widget instance for adding it to viewport.
	ScoreWidgetClass = LoadClass<UScoreWidget>(nullptr, ScoreWidgetPath);

	if (PlayerCharacterController)
	{
		ScoreWidgetInstance = CreateWidget<UScoreWidget>(PlayerCharacterController, ScoreWidgetClass);
		if (ScoreWidgetInstance)
		{
			ScoreWidgetInstance->AddToViewport();
		}
	}

	// Getting references.
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(World, 0));
	CameraComponent = PlayerCharacter->CameraComponent;

	TubeManager = PlatformerGameInstance->GetSubsystem<UTubeManagerSubsystem>();
	if (TubeManager)
	{
		TubeManager->GetAllTubes();
	}

	LoadSaves();
}

void AMainLevelScriptActor::ToggleInputMode() const
{
	if (!PlayerCharacterController)
	{
		return;
	}

	PlayerCharacterController->ToggleInputMode(InputMode);
}

void AMainLevelScriptActor::LoadSaves() const
{
	if (!PlatformerGameInstance)
	{
		return;
	}

	PlatformerGameInstance->LoadGame(World, UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex()), 0);
	PlatformerGameInstance->LoadBestScore(World, 0);
}

void AMainLevelScriptActor::SetScoreOnUI(const int32& Score) const
{
	ScoreWidgetInstance->SetScore(Score);
}

void AMainLevelScriptActor::SetBestScoreOnUI(const int32& Score) const
{
	ScoreWidgetInstance->SetBestScore(Score);
}

float AMainLevelScriptActor::GetPPWeight() const
{
	return PPWeight;
}

void AMainLevelScriptActor::SetPPWeight(float Weight)
{
	// Post processing weight, clamped between 0 and 1.
	PPWeight = FMath::Clamp(Weight, 0.f, 1.f);
	SetPostProcessingEffectByWeight(PPWeight);
}

void AMainLevelScriptActor::SetPostProcessingEffectByWeight(const float& Weight)
{
	if (!PlayerCharacter)
	{
		return;
	}

	if (!CameraComponent)
	{
		return;
	}

	if (PlayerCharacter->CameraComponent->PostProcessSettings.WeightedBlendables.Array.Num() <= 0)
	{
		return;
	}

	PlayerCharacter->CameraComponent->PostProcessSettings.WeightedBlendables.Array[0].Weight = Weight;
}