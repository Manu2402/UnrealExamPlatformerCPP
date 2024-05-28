// Header wrotes in this way before the tip gave from professor about separate "Private and Public" files.
#include "../Public/PlayerMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PlayerJumpForce = 600;
	MovementSpeed = 400;
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Owner = Cast<ACharacter>(GetOwner());
	if (!Owner)
	{
		return;
	}

	World = Owner->GetWorld();
	if (!World)
	{
		return;
	}

	// Apply gravity.
	if (!bIsGrounded)
	{
		Velocity += Gravity;
	}
	// If Velocity is 0 than character is grounded.
	bIsGrounded = Velocity.Z == 0;

	// Sphere to track if there are some collision under of character.
	SphereParams.SphereLocation = Owner->GetActorLocation() + DefaultSphereOffset;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	if (!World->SweepSingleByChannel(HitResult, SphereParams.SphereLocation, SphereParams.SphereLocation, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(DefaultSphereRadius), QueryParams))
	{
		bIsGrounded = false;
	}
	// DrawDebugSphere(World, SphereParams.SphereLocation, DefaultSphereRadius, 32, FColor::Green);

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
	CurrentSign = Direction > 0;

	if (PreviousSign != CurrentSign)
	{
		Owner->GetMesh()->AddWorldRotation(FRotator(0, 180, 0));
	}

	Velocity += UpdatedComponent->GetRightVector() * Direction * MovementSpeed;
	PreviousSign = CurrentSign;
}
