#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/Character.h"
#include "PlayerMovementComponent.generated.h"

USTRUCT()
struct FSphereParams
{
	GENERATED_BODY()

	FVector SphereLocation;
	float SphereRadius;
};

UCLASS()
class UNREALPLATFORMERCPP_API UPlayerMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
private:
	const FVector& Gravity = FVector(0, 0, -9.81f);
	const FVector& DefaultSphereOffset = FVector(0, 0, -90);
	const FQuat& OffsetRotation = FQuat(FRotator(0.f, 180.f, 0.f));
	const float& DefaultSphereRadius = 15;
	const float& ZScaleMax = 30;

	class USkeletalMeshComponent* SkeletalMesh;

	// Flip look at.
	bool bPreviousSign;
	bool bCurrentSign;

	bool bCanMoveOnYAxisForward = true;
	bool bCanMoveOnYAxisBackward = true;

	FHitResult HitResult;
	FSphereParams SphereParams;
	ACharacter* Owner;
	UWorld* World;
	
public:
	UPlayerMovementComponent();

	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerJumpForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsGrounded = false;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayerJump();
	void PlayerMove(const struct FInputActionValue& Input);
	void AbilityToMoveOnY(bool Value);
};
