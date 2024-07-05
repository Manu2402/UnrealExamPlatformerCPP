#include "Utility/Subsystems/TubeManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Tube.h"

/* This class handle all the tubes in the game. Cause in this game the tubes are as teleports, and 
they can be enabled/disabled. All is handled even to the save game info. */

TMap<ATube*, bool> UTubeManagerSubsystem::GetTubesState() const
{
	if (TubesState.IsEmpty())
	{
		return TMap<ATube*, bool>();
	}

	return TubesState;
}

void UTubeManagerSubsystem::SetTubesState(const TMap<ATube*, bool>& NewTubesState)
{
	TubesState = NewTubesState;
}

TArray<ATube*> UTubeManagerSubsystem::GetAllTubes()
{
	World = GetWorld();

	Tubes.Empty();
	TArray<AActor*> OutTubes;
	UGameplayStatics::GetAllActorsOfClass(World, ATube::StaticClass(), OutTubes);

	for (AActor* Tube : OutTubes)
	{
		ATube* CurrentTube = Cast<ATube>(Tube);
		if (!CurrentTube)
		{
			UE_LOG(LogTemp, Error, TEXT("Error: unless a tube isn't found!"));
			return TArray<ATube*>();
		}

		Tubes.Add(CurrentTube);
	}

	for (auto& TubeState : TubesState)
	{
		if (Tubes.Contains(TubeState.Key))
		{
			TubeState.Key->SetActive(TubesState[TubeState.Key]);
		}
	}

	return Tubes;
}

void UTubeManagerSubsystem::ToggleTubeQuestState(const FName& TubeQuestStateString, const bool& bState)
{
	GetAllTubes();
	for (ATube* Tube : Tubes)
	{
		if (!Tube->ActorHasTag(TubeQuestStateString))
		{
			continue;
		}

		TubesState.Add(Tube, bState);
		Tube->SetActive(bState);
	}
}

void UTubeManagerSubsystem::ClearTubesState()
{
	TubesState.Empty();
}
