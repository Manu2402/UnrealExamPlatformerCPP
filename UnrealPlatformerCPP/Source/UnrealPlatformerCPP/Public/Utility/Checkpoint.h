#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	const FVector& TriggerExtendParams = FVector(32, 32, 32);
	class UBoxComponent* SaveTrigger;
	
	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
