#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "DataAsset_IA.generated.h"

// Using DataAsset to managing better all of Input Actions. 
UCLASS()
class UNREALPLATFORMERCPP_API UDataAsset_IA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputActions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputActions")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputActions")
	UInputAction* PauseAction;
	
};
