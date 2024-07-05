#include "Widgets/ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Player/PlayerCharacterState.h"
#include "Kismet/GameplayStatics.h"

void UScoreWidget::NativeConstruct()
{
	APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return;
	}

	SetScore(PlayerCharacterState->GetCurrentScore());
	SetBestScore(PlayerCharacterState->GetBestScore());
}

void UScoreWidget::SetScore(const int32 Score)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}

void UScoreWidget::SetBestScore(const int32 Score)
{
	if (Score < 0)
	{
		BestScoreText->SetText(VoidBestScore);
		return;
	}

	BestScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}