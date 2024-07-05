#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BestScoreSaveGame.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UBestScoreSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UBestScoreSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 BestScore;
	
};
