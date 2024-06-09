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
	const FVector& FlagMeshLocation = FVector(0, -80, -30);
	const FRotator& FlagMeshRotation = FRotator(0, 0, 90);
	const FVector& FlagMeshScale = FVector(0.6);

	bool CurrentState;

	class UBoxComponent* SaveTrigger;
	class USkeletalMeshComponent* FlagMesh;
	
	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void ToggleFlagState(bool State);
};
