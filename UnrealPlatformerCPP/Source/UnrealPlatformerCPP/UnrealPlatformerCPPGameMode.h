#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealPlatformerCPPGameMode.generated.h"


UCLASS()
class UNREALPLATFORMERCPP_API AUnrealPlatformerCPPGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	const FString DefaultPawnBPClassPath = TEXT("/Game/Custom/Blueprints/BP_PlayerPawn.BP_PlayerPawn_C");

public:
	AUnrealPlatformerCPPGameMode();

};
