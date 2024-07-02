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

	int32 GetCurrentScore() const;
	void SetCurrentScore(const int32& NewScore);
	bool Losing() const;

	int32 GetBestScore() const;
	void SetBestScore(const int32& NewScore);

private:
	const int32& StartScore = 100;
	const int32& StartBestScore = -1;

	int32 CurrentScore;
	int32 BestScore;

};
