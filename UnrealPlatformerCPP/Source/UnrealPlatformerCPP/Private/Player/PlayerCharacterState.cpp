#include "Player/PlayerCharacterState.h"

APlayerCharacterState::APlayerCharacterState()
{
	CurrentScore = StartScore;
	BestScore = StartBestScore;
}

int32 APlayerCharacterState::GetCurrentScore() const
{
	return CurrentScore;
}

void APlayerCharacterState::SetCurrentScore(const int32& NewScore)
{
	CurrentScore = NewScore > 0 ? NewScore : 0;
}

void APlayerCharacterState::RemoveScore(const int32& ScoreToRemove)
{
	CurrentScore -= ScoreToRemove;
}

bool APlayerCharacterState::Losing() const
{
	return CurrentScore <= 0;
}

int32 APlayerCharacterState::GetBestScore() const
{
	return BestScore;
}

void APlayerCharacterState::SetBestScore(const int32& NewScore)
{
	BestScore = NewScore;
}