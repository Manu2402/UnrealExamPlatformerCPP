#include "PlayerMovementComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	bIsGrounded = false;
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsGrounded)
	{
		Velocity += Gravity;
	}

}

void UPlayerMovementComponent::PlayerJump(float& PlayerJumpForce)
{
	Velocity = UpdatedComponent->GetUpVector() * PlayerJumpForce;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Jump"));
}
