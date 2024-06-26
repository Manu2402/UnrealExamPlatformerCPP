#include "Widgets/ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::NativeConstruct()
{
	SetScore(250);
}

void UScoreWidget::SetScore(int32 Score)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}
