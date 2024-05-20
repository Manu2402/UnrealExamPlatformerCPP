#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Utility/DataAssets/DataAsset_IA.h"
#include "../PlayerMovementComponent/PlayerMovementComponent.h"
#include "PlayerCharacter.generated.h"

// Forward declaration about UInputMappingContext.
class UInputMappingContext;
class UInputAction;

UCLASS()
class UNREALPLATFORMERCPP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	const FVector CameraOffset = FVector(-660, 0, 60);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UDataAsset_IA* DataAsset_IA; // Database composed by input action assets.

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void PlayerJump();

	UFUNCTION(BlueprintCallable)
	void PlayerMove(const FInputActionValue& Input);

};
