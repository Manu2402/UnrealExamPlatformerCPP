#include "Widgets/SlotsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"

void USlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotZero)
	{
		SlotZero->OnClicked.AddDynamic(this, &USlotsWidget::InitSlotZero);
	}

	if (SlotOne)
	{
		SlotOne->OnClicked.AddDynamic(this, &USlotsWidget::InitSlotOne);
	}

	if (SlotTwo)
	{
		SlotTwo->OnClicked.AddDynamic(this, &USlotsWidget::InitSlotTwo);
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	PlatformerGameInstance = GameInstance->GetSubsystem<UPlatformerGameInstance>();
}

void USlotsWidget::InitSlotZero()
{
	PlatformerGameInstance->SetCurrentSlotIndex(ESlotsIndex::Zero);
	LoadLevel();
}

void USlotsWidget::InitSlotOne()
{
	PlatformerGameInstance->SetCurrentSlotIndex(ESlotsIndex::One);
	LoadLevel();
}

void USlotsWidget::InitSlotTwo()
{
	PlatformerGameInstance->SetCurrentSlotIndex(ESlotsIndex::Two);
	LoadLevel();
}

void USlotsWidget::LoadLevel()
{
	FString SlotName = UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex());
	PlatformerGameInstance->LoadGame(GetWorld(), SlotName, 0);
	UGameplayStatics::OpenLevel(GetWorld(), PlatformerGameInstance->MainLevelName);
}