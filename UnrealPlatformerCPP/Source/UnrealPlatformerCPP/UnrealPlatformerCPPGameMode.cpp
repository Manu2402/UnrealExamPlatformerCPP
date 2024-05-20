#include "UnrealPlatformerCPPGameMode.h"
#include "PlayerCharacter/PlayerCharacter.h"

AUnrealPlatformerCPPGameMode::AUnrealPlatformerCPPGameMode()
{
	// Set my BP_PlayerPawn as default class getting it class. 
	static ConstructorHelpers::FClassFinder<ACharacter> DefaultBPPawnClass(*DefaultPawnBPClassPath);
	if (DefaultBPPawnClass.Class)
	{
		DefaultPawnClass = DefaultBPPawnClass.Class;
	}
}