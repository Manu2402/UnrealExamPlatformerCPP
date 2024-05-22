#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "PlayerMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FLineTraceParameters
{
	GENERATED_BODY()

	FVector StartLocation;
	FVector Direction;
	float LineLength;
};

UCLASS(BlueprintType, Blueprintable)
class UNREALPLATFORMERCPP_API UPlayerMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
private:
	const FVector Gravity = FVector(0, 0, -9.81f);
	const float DefaultLineLength = 100;

	AActor* Owner;
	FHitResult HitResult;
	FLineTraceParameters LineTraceParameters;
	UWorld* World;
	
public:
	UPlayerMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerJumpForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsGrounded = false;

	void SetIsGrounded(const bool Value);

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayerJump();

	void PlayerMove(const struct FInputActionValue& Input);

};
