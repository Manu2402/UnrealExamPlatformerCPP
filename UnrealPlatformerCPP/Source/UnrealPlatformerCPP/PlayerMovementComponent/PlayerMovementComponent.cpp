#include "PlayerMovementComponent.h"
#include "EnhancedInputComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PlayerJumpForce = 400;
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsGrounded)
	{
		Velocity += Gravity;
	}

	bIsGrounded = false;

	FHitResult HitResult;

	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, FRotator::ZeroRotator, true, HitResult))
	{
		FVector Compenetration = GetPenetrationAdjustment(HitResult);
		ResolvePenetration(Compenetration, HitResult, UpdatedComponent->GetComponentQuat());

		if (HitResult.Normal.Z > 0)
		{
			bIsGrounded = true;
		}
	}
}

void UPlayerMovementComponent::PlayerJump()
{
	if (!bIsGrounded)
	{
		return;
	}

	Velocity = UpdatedComponent->GetUpVector() * PlayerJumpForce;
}

void UPlayerMovementComponent::PlayerMove(const FInputActionValue& Input)
{
	const float Direction = Input.Get<float>();
	Velocity += UpdatedComponent->GetRightVector() * Direction * MovementSpeed;
}
