#include "UnrealPlatformerCPPGameMode.h"
#include "PlayerPawn/PlayerPawn.h"

AUnrealPlatformerCPPGameMode::AUnrealPlatformerCPPGameMode()
{
	// Set my BP_PlayerPawn as default class getting it class. 
	static ConstructorHelpers::FClassFinder<APawn> DefaultBPPawnClass(*DefaultPawnBPClassPath);
	if (DefaultBPPawnClass.Class)
	{
		DefaultPawnClass = DefaultBPPawnClass.Class;
	}
}