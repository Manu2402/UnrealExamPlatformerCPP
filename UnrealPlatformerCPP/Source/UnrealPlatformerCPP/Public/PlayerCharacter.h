#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utility/DataAssets/DataAsset_IA.h"
#include "PlayerMovementComponent.h"
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

	UWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* MovementCheckCollider;

	// Translate all this into playercontroller
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UDataAsset_IA* DataAsset_IA; // Database composed by input action assets.

private:
	const FVector& CameraOffset = FVector(-660, 0, 60);
	const FVector& MovementCheckBoxExtents = FVector(32, 32, 80);
	const FName& PlayerTagName = TEXT("Player");
	
	UFUNCTION()
	void OnBoxExitTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PlayerJump();
	void PlayerMove(const FInputActionValue& Input);
	void BackMenu();
};