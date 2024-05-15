#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "PlayerMovementComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UNREALPLATFORMERCPP_API UPlayerMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
private:
	const FVector Gravity = FVector(0, 0, -9.81f);

	bool bIsGrounded;
	
public:
	UPlayerMovementComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayerJump(float& PlayerJumpForce);
};
