#include "Utility/Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	SaveTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveTrigger"));
	SaveTrigger->SetBoxExtent(TriggerExtendParams);
	SaveTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBoxTriggered);
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
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UPlatformerGameInstance* PlatformerGameInstance = GameInstance->GetSubsystem<UPlatformerGameInstance>();
	if (PlatformerGameInstance)
	{
		FString SlotName = UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex());
		PlatformerGameInstance->SaveGame(GetWorld(), SlotName, 0);
	}
}
