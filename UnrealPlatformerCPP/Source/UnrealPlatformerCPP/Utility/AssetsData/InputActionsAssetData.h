#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "InputActionsAssetData.generated.h"

// Using DataAsset to managing better all of Input Actions. 
UCLASS()
class UNREALPLATFORMERCPP_API UInputActionsAssetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputActions")
	UInputAction* TestAction;
	
	// Add other actions..
};
