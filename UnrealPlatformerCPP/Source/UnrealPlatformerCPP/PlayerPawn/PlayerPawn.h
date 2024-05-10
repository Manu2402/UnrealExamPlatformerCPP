#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
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

	USkeletalMeshComponent* SkeletalMeshComponent;
	UCameraComponent* CameraComponent;

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* TestAction;
	
	UFUNCTION()
	void Test(const FInputActionValue& Value);
};
