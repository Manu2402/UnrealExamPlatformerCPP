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

private:
	const int32 StartPoints = 100;
	int32 CurrentPoints;
	
};
