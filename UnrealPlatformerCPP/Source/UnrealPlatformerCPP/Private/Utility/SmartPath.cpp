#include "Utility/SmartPath.h"
#include "Components/SplineComponent.h"

ASmartPath::ASmartPath()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void ASmartPath::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASmartPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> ASmartPath::GetSplinePoints() const
{
	if (!SplineComponent)
	{
		return TArray<FVector>();
	}

	TArray<FVector> OutPoints;
	int32 NumberOfPoints = SplineComponent->GetNumberOfSplinePoints();
	for (int32 SplinePointsIndex = 0; SplinePointsIndex < NumberOfPoints; SplinePointsIndex++)
	{
		OutPoints.Add(SplineComponent->GetLocationAtSplinePoint(SplinePointsIndex, ESplineCoordinateSpace::World));
	}

	return OutPoints;
}

FVector ASmartPath::GetSplinePointAtIndex(const int32 Index) const
{
	return SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
}