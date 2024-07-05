#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"
#include "AI/Enemy.h"
#include "Perception/AISense_Sight.h"

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

	PlayerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerCollider"));
	if (PlayerCollider)
	{
		PlayerCollider->SetBoxExtent(MovementCheckBoxExtents);

		PlayerCollider->bHiddenInGame = false;
		PlayerCollider->SetupAttachment(RootComponent);

		// Collider overlap events.
		PlayerCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnBoxExitTrigger);
		PlayerCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleHit);
	}

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMovementComponent"));

	CameraComponent->SetupAttachment(RootComponent);

	// Setting ABP.
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("/Game/Custom/Blueprints/ABP/ABP_PlayerCharacter.ABP_PlayerCharacter"));
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleHit);

	PerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComponent"));
	PerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	PerceptionStimuliSource->RegisterWithPerceptionSystem();
}

void APlayerCharacter::OnBoxExitTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerMovementComponent->AbilityToMoveOnY(true);
}

void APlayerCharacter::OnCapsuleHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(EnemyTag))
	{
		return;
	}

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (!Enemy)
	{
		return;
	}

	Enemy->ToggleScore(Enemy->EnemyScoreToSubtract);
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