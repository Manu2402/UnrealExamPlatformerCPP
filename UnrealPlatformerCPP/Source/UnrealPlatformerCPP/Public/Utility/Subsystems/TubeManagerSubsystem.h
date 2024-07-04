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
	TMap<class ATube*, bool> TubesState;

public:
	TMap<class ATube*, bool> GetTubesState() const;
	void SetTubesState(const TMap<class ATube*, bool>& NewTubesState);

	TArray<class ATube*> GetAllTubes();
	void ToggleTubeQuestState(const FName& TubeQuestStateName, const bool bState);
	void ClearTubesState();
	
};