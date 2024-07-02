#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(PlayerTagName);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if (CameraComponent)
	{
		// Camera position.
		CameraComponent->SetWorldLocation(GetActorLocation() - CameraOffset);
	}

	MovementCheckCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MovementCheckCollider"));
	if (MovementCheckCollider)
	{
		MovementCheckCollider->SetBoxExtent(MovementCheckBoxExtents);

		MovementCheckCollider->bHiddenInGame = false;
		MovementCheckCollider->SetupAttachment(RootComponent);

		// Collider overlap events.
		MovementCheckCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnBoxExitTrigger);
	}

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMovementComponent"));

	CameraComponent->SetupAttachment(RootComponent);

	// Setting ABP.
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("/Game/Custom/Blueprints/ABP_PlayerCharacter.ABP_PlayerCharacter"));
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);
	}
}

void APlayerCharacter::OnBoxExitTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerMovementComponent->AbilityToMoveOnY(true);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced input.
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!Subsystem)
	{
		return;
	}

	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!Input)
	{
		return;
	}

	Input->BindAction(DataAsset_IA->JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::PlayerJump);
	Input->BindAction(DataAsset_IA->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayerMove);
	Input->BindAction(DataAsset_IA->PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::BackMenu);
}

void APlayerCharacter::PlayerJump()
{
	PlayerMovementComponent->PlayerJump();
}

void APlayerCharacter::PlayerMove(const FInputActionValue& Input)
{
	PlayerMovementComponent->PlayerMove(Input);
}

void APlayerCharacter::BackMenu()
{
	UPlatformerGameInstance* PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!PlatformerGameInstance)
	{
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), PlatformerGameInstance->SlotsLevelName);
}