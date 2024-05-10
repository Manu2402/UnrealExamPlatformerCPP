#include "PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	const FString SkeletalMeshPath("/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny");
	const FString CameraText("Camera");

	SetActorRotation(StartRotation);

	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(*CameraText);
	if (CameraComponent)
	{
		CameraComponent->SetWorldLocation(GetActorLocation() - CameraOffset);
	}

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
		Input->BindAction(TestAction, ETriggerEvent::Triggered, this, &APlayerPawn::Test);
	}
}

void APlayerPawn::Test(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Test"));
}

