#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ToggleScore.h"
#include "PlatformEE.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API APlatformEE : public AActor, public IToggleScore
{
	GENERATED_BODY()
	
public:	
	APlatformEE();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	const TCHAR* CubeMeshPath = TEXT("/Engine/BasicShapes/Cube.Cube");
	const TCHAR* GrayMaterialPath = TEXT("/Game/Custom/Materials/M_Gray.M_Gray");

	const FVector& TriggerExtendParams = FVector(40, 40, 10);
	const FVector& TriggerLocation = FVector(0, 0, 10);
	const FVector& MeshScaleParams = FVector(1, 1, 0.08);
	
	const int32 PlatformEEScore = 666; // EE = Easter Egg.

	UWorld* World;
	ULevel* CurrentLevel;
	class AMainLevelScriptActor* MainLevelScriptActor;
	class APlayerCharacterState* PlayerCharacterState;

	bool bIsActive = true;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerCollider;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PlatformMeshComponent;

	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void ToggleScore(const int32& Score);

};
