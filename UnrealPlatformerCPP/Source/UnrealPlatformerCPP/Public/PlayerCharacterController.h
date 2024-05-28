#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:

	// Function that toggles input mode depending on a param.
	template<class T>
	void ToggleInputMode(T InputMode)
	{
		// Check if the template is unless a FInputModeDatabase.
		static_assert(std::is_base_of<FInputModeDataBase, T>::value, "Mush inherit from FInputModeDataBase");
		// If "InputMode" type, got with "decltype" keyword is the same of "FInputModeGameOnly", sets cursor visibility to off.
		SetInputMode(InputMode);

		if (std::is_same<decltype(InputMode), FInputModeGameOnly>::value)
		{
			bShowMouseCursor = false;
			return;
		}
		bShowMouseCursor = true;
	}

};
