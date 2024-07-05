#include "Widgets/SlotsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/PlatformerGameInstance.h"

void USlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind button events.
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

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	PlatformerGameInstance = Cast<UPlatformerGameInstance>(GameInstance);
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

void USlotsWidget::LoadLevel() const
{
	UGameplayStatics::OpenLevel(World, PlatformerGameInstance->MainLevelName);
}