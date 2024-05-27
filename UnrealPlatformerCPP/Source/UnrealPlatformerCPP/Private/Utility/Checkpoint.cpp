#include "Utility/Checkpoint.h"
#include "Components/BoxComponent.h"

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
	// Trigger save logic into a subsystem (game instance).
}
