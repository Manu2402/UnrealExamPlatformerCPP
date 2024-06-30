#include "Widgets/ScoreWidget.h"
#include "Components/TextBlock.h"
#include "PlayerCharacterState.h"
#include "Kismet/GameplayStatics.h"

void UScoreWidget::NativeConstruct()
{
	APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (PlayerCharacterState)
	{
		SetScore(PlayerCharacterState->GetCurrentScore());
		SetBestScore(PlayerCharacterState->GetBestScore());
	}
}

void UScoreWidget::SetScore(int32 Score)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}

void UScoreWidget::SetBestScore(int32 Score)
{
	if (Score < 0)
	{
		BestScoreText->SetText(VoidBestScore);
		return;
	}

	BestScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}