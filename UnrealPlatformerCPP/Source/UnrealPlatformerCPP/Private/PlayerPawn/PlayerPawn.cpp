// Header wrotes in this way before the tip gave from professor about separate "Private and Public" files.
#include "../Public/PlayerPawn/PlayerPawn.h" 

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	const FString CameraText("Camera");
	const FString SkeletalMeshPath("/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny");

	SetActorRotation(StartRotation);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(*CameraText);
	if (CameraComponent)
	{
		CameraComponent->SetWorldLocation(GetActorLocation() - CameraOffset);
	}

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMovementComponent"));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input)
	{
		Input->BindAction(DataAsset_IA->JumpAction, ETriggerEvent::Started, this, &APlayerPawn::PlayerJump);
		Input->BindAction(DataAsset_IA->MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::PlayerMove);
	}
}

void APlayerPawn::PlayerJump()
{
	PlayerMovementComponent->PlayerJump();
}

void APlayerPawn::PlayerMove(const FInputActionValue& Input)
{
	// Debug and fix movement.
	PlayerMovementComponent->PlayerMove(Input);
}