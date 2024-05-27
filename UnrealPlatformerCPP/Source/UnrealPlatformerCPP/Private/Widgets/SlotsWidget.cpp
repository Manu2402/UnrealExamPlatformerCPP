#include "Widgets/SlotsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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
}

void USlotsWidget::InitSlotZero()
{
	CurrentSlotIndex = ESlotsIndex::Zero;
	LoadLevel();
}

void USlotsWidget::InitSlotOne()
{
	CurrentSlotIndex = ESlotsIndex::One;
	LoadLevel();
}

void USlotsWidget::InitSlotTwo()
{
	CurrentSlotIndex = ESlotsIndex::Two;
	LoadLevel();
}

void USlotsWidget::LoadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainLevelName);
}