// Header wrotes in this way before the tip gave from professor about separate "Private and Public" files.
#include "../Public/PlayerMovementComponent/PlayerMovementComponent.h"

#include "EnhancedInputComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PlayerJumpForce = 600;
	MovementSpeed = 400;
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsGrounded)
	{
		Velocity += Gravity;
	}

	// Check about isGrounded.
	bIsGrounded = Velocity.Z == 0;

	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, FRotator::ZeroRotator, true, HitResult))
	{
		FVector Compenetration = GetPenetrationAdjustment(HitResult);
		ResolvePenetration(Compenetration, HitResult, UpdatedComponent->GetComponentQuat());

		if (HitResult.Normal.Z > 0)
		{
			Velocity.Z = 0;
			bIsGrounded = true;
		}
	}

	Velocity.X = 0;
	Velocity.Y = 0;
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
