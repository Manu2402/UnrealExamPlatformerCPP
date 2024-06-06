#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/Character.h"
#include "PlayerMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FSphereParams
{
	GENERATED_BODY()

	FVector SphereLocation;
	float SphereRadius;
};

UCLASS(BlueprintType, Blueprintable)
class UNREALPLATFORMERCPP_API UPlayerMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
private:
	const FVector Gravity = FVector(0, 0, -9.81f);
	const FVector DefaultSphereOffset = FVector(0, 0, -90);
	const float DefaultSphereRadius = 20;

	// Flip look at.
	bool bPreviousSign = true;
	bool bCurrentSign;

	bool bCanMoveOnYAxisForward = true;
	bool bCanMoveOnYAxisBackward = true;

	FHitResult HitResult;
	FSphereParams SphereParams;
	ACharacter* Owner;
	UWorld* World;
	
public:
	UPlayerMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerJumpForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsGrounded = false;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayerJump();

	void PlayerMove(const struct FInputActionValue& Input);
};
