#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"


UCLASS()
class UNREALPLATFORMERCPP_API APlayerCharacterState : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerCharacterState();
	int32 GetCurrentPoints() const;
	void SetCurrentPoints(const int32 Points);

private:
	const int32 StartPoints = 100;
	int32 CurrentPoints;
	
};
