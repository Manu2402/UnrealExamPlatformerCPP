#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TubeManagerSubsystem.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UTubeManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UWorld* World;
	TArray<class ATube*> Tubes;

public:
	TArray<class ATube*> GetAllTubes();
	void ToggleTubeQuestState(const FName& TubeQuestStateName, const bool bState);
	
};