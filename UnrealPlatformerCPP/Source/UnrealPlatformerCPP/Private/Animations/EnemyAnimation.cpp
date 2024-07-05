#include "Animations/EnemyAnimation.h"
#include "AI/Enemy.h"
#include "GameFramework/PawnMovementComponent.h"

/* Same as character animation class, but using the standard movement component. */

void UEnemyAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AEnemy* Character = Cast<AEnemy>(TryGetPawnOwner());
	if (!Character)
	{
		return;
	}

	MovementComponent = Character->GetMovementComponent();
}

void UEnemyAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent)
	{
		return;
	}

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size();

	bShouldMove = GroundSpeed > 0;

	bIsFalling = MovementComponent->IsFalling();
}