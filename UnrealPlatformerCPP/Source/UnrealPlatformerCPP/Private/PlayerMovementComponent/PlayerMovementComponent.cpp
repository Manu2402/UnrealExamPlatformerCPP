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

	Owner = GetOwner();
	World = Owner->GetWorld();

	if (!bIsGrounded)
	{
		Velocity += Gravity;
	}
	else
	{
		Velocity.Z = 0;
	}

	LineTraceParameters.StartLocation = Owner->GetActorLocation();
	LineTraceParameters.Direction = FVector::DownVector;
	LineTraceParameters.LineLength = DefaultLineLength;
	FVector EndLocation = LineTraceParameters.StartLocation + LineTraceParameters.Direction * LineTraceParameters.LineLength;

	bIsGrounded = World->LineTraceSingleByChannel(HitResult, LineTraceParameters.StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(World, LineTraceParameters.StartLocation, EndLocation, FColor::Green);

	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, FRotator::ZeroRotator, true, HitResult))
	{
		FVector Compenetration = GetPenetrationAdjustment(HitResult);
		ResolvePenetration(Compenetration, HitResult, UpdatedComponent->GetComponentQuat());
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
	
	//bIsGrounded = false;
	Velocity = UpdatedComponent->GetUpVector() * PlayerJumpForce;
}

void UPlayerMovementComponent::PlayerMove(const FInputActionValue& Input)
{
	const float Direction = Input.Get<float>();
	Velocity += UpdatedComponent->GetRightVector() * Direction * MovementSpeed;
}
