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
	// Materials.
	const TCHAR* CheckpointMeshPath = TEXT("/Game/Custom/Meshes/Flags/Checkpoint_Flag/Checkpoint_Flag.Checkpoint_Flag");
	const TCHAR* GreenMaterialPath = TEXT("/Game/Custom/Materials/M_Green.M_Green");
	const TCHAR* RedMaterialPath = TEXT("/Game/Custom/Materials/M_Red.M_Red");

	const FVector& TriggerExtendParams = FVector(32);
	const FVector& FlagMeshLocation = FVector(0, -80, -30);
	const FRotator& FlagMeshRotation = FRotator(0, 0, 90);
	const FVector& FlagMeshScale = FVector(0.6f);

	bool bCurrentState;

	class UBoxComponent* SaveTrigger;
	class USkeletalMeshComponent* FlagMesh;
	
	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void ToggleFlagState(const bool bState);
};
