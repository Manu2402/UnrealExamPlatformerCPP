#include "Objects/Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Utility/PlatformerGameInstance.h"
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
	}

	FlagMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FlagMesh"));
	if (FlagMesh)
	{
		USkeletalMesh* Flag = LoadObject<USkeletalMesh>(nullptr, CheckpointMeshPath);
		if (!Flag)
		{
			return;
		}

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
	if (!bCurrentState)
	{
		return;
	}

	UPlatformerGameInstance* PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!PlatformerGameInstance)
	{
		return;
	}

	const FString& SlotName = UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex());
	if (!PlatformerGameInstance->SaveGame(GetWorld(), SlotName, 0))
	{
		return;
	}
		
	ToggleFlagState(false);
}

void ACheckpoint::ToggleFlagState(const bool bState)
{
	bCurrentState = bState;
	if (bCurrentState)
	{
		UMaterial* Material = LoadObject<UMaterial>(nullptr, GreenMaterialPath);
		FlagMesh->SetMaterial(1, Material);
	}
	else
	{
		UMaterial* Material = LoadObject<UMaterial>(nullptr, RedMaterialPath);
		FlagMesh->SetMaterial(1, Material);
	}
}