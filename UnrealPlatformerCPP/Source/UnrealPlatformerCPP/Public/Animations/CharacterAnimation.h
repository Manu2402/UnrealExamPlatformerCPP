#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsFalling;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class UPlayerMovementComponent* MovementComponent;
	
};
