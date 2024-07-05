// Header wrotes in this way before the tip gave from professor about separate "Private and Public" files.
#include "../Public/Player/PlayerMovementComponent.h"

#include "EnhancedInputComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PlayerJumpForce = 600; // Hard coded but c'est la vie.
	MovementSpeed = 400;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	if (!Owner)
	{
		return;
	}

	SkeletalMesh = Owner->GetMesh();
	if (!SkeletalMesh)
	{
		return;
	}

	// Setting initial forward.
	bPreviousSign = SkeletalMesh->GetRightVector().Y > 0;
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Owner)
	{
		return;
	}

	SkeletalMesh = Owner->GetMesh();
	if (!SkeletalMesh)
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

	if (!bCanMoveOnYAxisForward && Velocity.Y < 0)
	{
		bCanMoveOnYAxisForward = true;
	}
	if (!bCanMoveOnYAxisBackward && Velocity.Y > 0)
	{
		bCanMoveOnYAxisBackward = true;
	}

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
		Owner->AddActorWorldOffset(-HitResult.ImpactNormal);

		// Check about platform collisions.
		if (HitResult.Normal.Z > HitNormalValue)
		{
			Velocity.Z = 0;
			bIsGrounded = true;
		}

		if (HitResult.Normal.Y < -HitNormalValue)
		{
			Velocity.Y = 0;
			bCanMoveOnYAxisForward = false;
		}

		if (HitResult.Normal.Y > HitNormalValue)
		{
			Velocity.Y = 0;
			bCanMoveOnYAxisBackward = false;
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
	bCurrentSign = Direction > 0;

	FVector MoveDirection = UpdatedComponent->GetRightVector() * Direction * MovementSpeed;

	if (bPreviousSign != bCurrentSign)
	{
		SkeletalMesh->AddWorldRotation(OffsetRotation);
	}

	if (!bCanMoveOnYAxisForward && MoveDirection.Y > 0)
	{
		MoveDirection.Y = 0;
	}
	if (!bCanMoveOnYAxisBackward && MoveDirection.Y < 0)
	{
		MoveDirection.Y = 0;
	}

	Velocity += MoveDirection;

	bPreviousSign = bCurrentSign;
}

void UPlayerMovementComponent::AbilityToMoveOnY(const bool& bValue)
{
	bCanMoveOnYAxisForward = bValue;
	bCanMoveOnYAxisBackward = bValue;
}