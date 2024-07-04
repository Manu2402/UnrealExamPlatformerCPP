#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ToggleScore.h"
#include "Enemy.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API AEnemy : public ACharacter, public IToggleScore
{
	GENERATED_BODY()

public:
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UBoxComponent* DamageCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class ASmartPath* PawnPath;

	const int32& EnemyScoreToSubtract = 25;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ToggleScore(const int32& Score);

private:
	const TCHAR* SkeletalMeshPath = TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin");
	const FVector& DamageColliderExtent = FVector(5, 5, 5);
	const FName& DamageSocketString = TEXT("DamageSocket");
	const FName& FirstFloorQuestString = TEXT("FirstFloorQuest");
	const FName& PlayerTag = TEXT("Player");
	const FName& EnemyTag = TEXT("Enemy");

	UWorld* World;
	ULevel* CurrentLevel;
	USkeletalMeshComponent* SkeletalMeshComponent;
	class APlayerCharacterState* PlayerCharacterState;
	class AMainLevelScriptActor* MainLevelScriptActor;
	class UPlatformerGameInstance* PlatformerGameInstance;
	class UTubeManagerSubsystem* TubeManager;

	UFUNCTION()
	void OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void DisableEnemy(const bool bValue);

};
