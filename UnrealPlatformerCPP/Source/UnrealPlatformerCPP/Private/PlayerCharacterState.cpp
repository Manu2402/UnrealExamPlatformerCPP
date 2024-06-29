#include "PlayerCharacterState.h"
#include "Kismet/GameplayStatics.h"

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
	CurrentPoints = Points > 0 ? Points : 0;
}

bool APlayerCharacterState::Losing() const
{
	return CurrentPoints <= 0;
}
