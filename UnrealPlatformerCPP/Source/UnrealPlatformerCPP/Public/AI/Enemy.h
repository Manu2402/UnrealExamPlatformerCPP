#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API AEnemy : public ACharacter
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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	const TCHAR* SkeletalMeshPath = TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin");
	const FName& DamageSocketString = TEXT("DamageSocket");

	USkeletalMeshComponent* SkeletalMeshComponent;

};
