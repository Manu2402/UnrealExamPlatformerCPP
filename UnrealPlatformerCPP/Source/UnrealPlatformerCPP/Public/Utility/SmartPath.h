#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartPath.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API ASmartPath : public AActor
{
	GENERATED_BODY()
	
public:	
	ASmartPath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* SplineComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	TArray<FVector> GetSplinePoints() const;

	UFUNCTION()
	FVector GetSplinePointAtIndex(const int32& Index) const;

};
