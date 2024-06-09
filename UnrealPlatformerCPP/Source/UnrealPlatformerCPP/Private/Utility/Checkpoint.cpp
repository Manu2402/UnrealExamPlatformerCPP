#include "Utility/Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SaveTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveTrigger"));
	if (SaveTrigger)
	{
		SaveTrigger->SetBoxExtent(TriggerExtendParams);
		SaveTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBoxTriggered);

		SaveTrigger->SetupAttachment(RootComponent);
		SaveTrigger->bHiddenInGame = false;
	}

	FlagMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FlagMesh"));
	if (FlagMesh)
	{
		USkeletalMesh* Flag = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Custom/Meshes/Flags/Checkpoint_Flag/Checkpoint_Flag.Checkpoint_Flag"));
		FlagMesh->SetSkeletalMesh(Flag);

		FlagMesh->SetupAttachment(RootComponent);

		FlagMesh->SetRelativeLocation(FlagMeshLocation);
		FlagMesh->SetRelativeRotation(FlagMeshRotation);
		FlagMesh->SetRelativeScale3D(FlagMeshScale);

		// Changing color of the flag:
		// Green = triggerable
		// Red = triggerated
		ToggleFlagState(true);
	}
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

}

void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CurrentState)
	{
		return;
	}
	UPlatformerGameInstance* PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PlatformerGameInstance)
	{
		FString SlotName = UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex());
		if (PlatformerGameInstance->SaveGame(GetWorld(), SlotName, 0))
		{
			ToggleFlagState(false);
		}
	}
}

void ACheckpoint::ToggleFlagState(bool State)
{
	CurrentState = State;
	if (CurrentState)
	{
		UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Materials/M_Green.M_Green"));
		FlagMesh->SetMaterial(1, Material);
	}
	else
	{
		UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Materials/M_Red.M_Red"));
		FlagMesh->SetMaterial(1, Material);
	}
}