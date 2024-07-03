#include "Animations/CharacterAnimation.h"
#include "PlayerCharacter.h"
#include "PlayerMovementComponent.h"

void UCharacterAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APlayerCharacter* Character = Cast<APlayerCharacter>(TryGetPawnOwner());
	if(!Character)
	{
		return;
	}

	MovementComponent = Character->PlayerMovementComponent;

}

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent)
	{
		return;
	}

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size();
	
	bShouldMove = GroundSpeed > 0;

	bIsFalling = !MovementComponent->bIsGrounded;
}