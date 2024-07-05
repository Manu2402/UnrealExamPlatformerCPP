#include "Animations/CharacterAnimation.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerMovementComponent.h"

/* In this class i managed all the variabiles bound to the anim graph, and i applied this class as the
parent class of the animation bluprints that i used to animate both enemy and player. For the movement
i used the custom movement component on the player. */

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