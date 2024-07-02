#include "Utility/Subsystems/TubeManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Tube.h"

TArray<ATube*> UTubeManagerSubsystem::GetAllTubes()
{
	World = GetWorld();

	TArray<AActor*> OutTubes;
	UGameplayStatics::GetAllActorsOfClass(World, ATube::StaticClass(), OutTubes);

	for (AActor* Tube : OutTubes)
	{
		ATube* CurrentTube = Cast<ATube>(Tube);
		if (!CurrentTube)
		{
			return TArray<ATube*>();
			UE_LOG(LogTemp, Error, TEXT("Error: unless a tube isn't found!"));
		}

		Tubes.Add(CurrentTube);
	}

	return Tubes;
}

void UTubeManagerSubsystem::ToggleTubeQuestState(const FName& TubeQuestStateString, const bool bState)
{
	for (ATube* Tube : Tubes)
	{
		if (!Tube->ActorHasTag(TubeQuestStateString))
		{
			continue;
		}

		Tube->SetState(bState);
	}
}