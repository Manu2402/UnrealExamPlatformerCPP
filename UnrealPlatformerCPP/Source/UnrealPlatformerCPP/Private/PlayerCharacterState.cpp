#include "PlayerCharacterState.h"

APlayerCharacterState::APlayerCharacterState()
{
	CurrentPoints = StartPoints;
}

int32 APlayerCharacterState::GetCurrentPoints() const
{
	return CurrentPoints;
}

void APlayerCharacterState::SetCurrentPoints(const int32 Points)
{
	this->CurrentPoints = Points;
}