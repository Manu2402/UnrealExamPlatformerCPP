#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	const FRotator StartRotation = FRotator(0, 0, -90);
	// Change CameraOffset (more tall).
	const FVector CameraOffset = FVector(800, 0, 0);

	USkeletalMeshComponent* SkeletalMeshComponent;
	UCameraComponent* CameraComponent;

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
