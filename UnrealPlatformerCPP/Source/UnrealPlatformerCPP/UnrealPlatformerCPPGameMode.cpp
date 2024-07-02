#include "UnrealPlatformerCPPGameMode.h"
#include "PlayerCharacter.h"
// Header wrotes in this way before the tip gave from professor about separate "Private and Public" files.
#include "Public/PlayerCharacterController.h"
#include "PlayerCharacterState.h"

AUnrealPlatformerCPPGameMode::AUnrealPlatformerCPPGameMode()
{
	// Set my BP_PlayerPawn as default class getting it class. 
	static ConstructorHelpers::FClassFinder<ACharacter> DefaultBPPawnClass(*DefaultPawnBPClassPath);
	if (!DefaultBPPawnClass.Class)
	{
		return;
	}

	DefaultPawnClass = DefaultBPPawnClass.Class;
	PlayerControllerClass = APlayerCharacterController::StaticClass();
	PlayerStateClass = APlayerCharacterState::StaticClass();
}