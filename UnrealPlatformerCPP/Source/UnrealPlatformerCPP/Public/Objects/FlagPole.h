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
	// Materials.
	const TCHAR* FlagPoleMeshPath = TEXT("/Game/Custom/Meshes/Flags/FlagPole/SM_FlagPole.SM_FlagPole");
	const TCHAR* MaterialPath = TEXT("/Game/Custom/Meshes/Flags/FlagPole/Material.Material");
	const TCHAR* PipeMaterialPath = TEXT("/Game/Custom/Meshes/Flags/FlagPole/Pipe.Pipe");
	const TCHAR* YellowBallMaterialPath = TEXT("/Game/Custom/Meshes/Flags/FlagPole/Yellow_ball.Yellow_ball");
	const TCHAR* FlagMaterialPath = TEXT("/Game/Custom/Meshes/Flags/FlagPole/Flag.Flag");
	const TCHAR* BrickMaterialPath = TEXT("/Game/Custom/Meshes/Flags/FlagPole/Brick.Brick");

	const FVector& TriggerExtendParams = FVector(32);
	const FVector& FlagMeshLocation = FVector(0, -80, -30);
	const FVector& FlagMeshScale = FVector(0.6f);
	const FName& SlotsLevelName = TEXT("SlotsLevel");

	// I used a map to simplify the operations where i applied all materials to the flag.
	TMap<uint32, const TCHAR*> FlagPoleMaterials;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerCollider;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* FlagMesh;

	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void SetMaterials() const;

};
