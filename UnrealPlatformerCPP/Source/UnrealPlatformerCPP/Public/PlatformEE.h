#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformEE.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API APlatformEE : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformEE();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	const FVector& TriggerExtendParams = FVector(40, 40, 10);
	const FVector& TriggerLocation = FVector(0, 0, 10);
	const FVector& MeshScaleParams = FVector(1, 1, 0.1);

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerCollider;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PlatformMeshComponent;

	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
