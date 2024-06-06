#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Player"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if (CameraComponent)
	{
		CameraComponent->SetWorldLocation(GetActorLocation() - CameraOffset);
	}

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMovementComponent"));

	CameraComponent->SetupAttachment(RootComponent);

	// Set ABP.
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("/Game/Custom/Blueprints/ABP_PlayerCharacter.ABP_PlayerCharacter"));
	GetMesh()->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		Input->BindAction(DataAsset_IA->JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::PlayerJump);
		Input->BindAction(DataAsset_IA->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayerMove);
		Input->BindAction(DataAsset_IA->PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::Pause);
	}
}

void APlayerCharacter::PlayerJump()
{
	PlayerMovementComponent->PlayerJump();
}

void APlayerCharacter::PlayerMove(const FInputActionValue& Input)
{
	PlayerMovementComponent->PlayerMove(Input);
}

void APlayerCharacter::Pause()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UPlatformerGameInstance* PlatformerGameInstance = GameInstance->GetSubsystem<UPlatformerGameInstance>();
	UGameplayStatics::OpenLevel(GetWorld(), PlatformerGameInstance->SlotsLevelName);
}