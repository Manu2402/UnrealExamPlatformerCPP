#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "../Utility/DataAssets/DataAsset_IA.h"
#include "../PlayerMovementComponent/PlayerMovementComponent.h"
#include "PlayerPawn.generated.h"

// Forward declaration about UInputMappingContext.
class UInputMappingContext;
class UInputAction;

UCLASS()
class UNREALPLATFORMERCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	const FRotator StartRotation = FRotator(0, 0, -90);
	const FVector CameraOffset = FVector(700, 0, -200);

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UDataAsset_IA* DataAsset_IA; // Database composed by input action assets.
	
	UFUNCTION(BlueprintCallable)
	void PlayerJump();

	UFUNCTION(BlueprintCallable)
	void PlayerMove(const FInputActionValue& Input);

};
