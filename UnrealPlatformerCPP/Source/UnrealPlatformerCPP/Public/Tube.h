#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tube.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API ATube : public AActor
{
	GENERATED_BODY()
	
public:	
	ATube();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetState(bool value);

private:
	const FVector& TriggerExtendParams = FVector(45, 45, 32);
	const FVector& TriggerPosition = FVector(0, 0, -36);
	const FName& PlayerTag = TEXT("Player");
	const FName& NoCollisionPreset = TEXT("NoCollision");

	class UBoxComponent* TeleportTrigger;
	class UStaticMeshComponent* TubeMeshComponent;
	class UStaticMesh* TubeMesh;

	bool State = true;

	UPROPERTY(EditInstanceOnly)
	ATube* TeleportTube;

	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxExitTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
