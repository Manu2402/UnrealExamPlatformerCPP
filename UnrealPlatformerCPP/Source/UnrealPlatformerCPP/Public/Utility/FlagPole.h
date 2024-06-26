#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlagPole.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API AFlagPole : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlagPole();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	const FVector& TriggerExtendParams = FVector(32, 32, 32);
	const FVector& FlagMeshLocation = FVector(0, -80, -30);
	const FVector& FlagMeshScale = FVector(0.6);
	const FName& SlotsLevelName = TEXT("SlotsLevel");

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerCollider;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* FlagMesh;

	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
