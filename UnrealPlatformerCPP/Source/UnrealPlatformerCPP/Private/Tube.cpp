#include "Tube.h"
#include "Components/BoxComponent.h"

ATube::ATube()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveTrigger"));
	TeleportTrigger->SetBoxExtent(TriggerExtendParams);
	TeleportTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATube::OnBoxTriggered);
	TeleportTrigger->OnComponentEndOverlap.AddDynamic(this, &ATube::OnBoxExitTrigger);

	// Temp
	TeleportTrigger->bHiddenInGame = false;
}

void ATube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATube::SetState(bool value)
{
	State = value;
}

void ATube::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!State)
	{
		return;
	}

	if (!OtherActor->ActorHasTag(PlayerTag) || !TeleportTube)
	{
		return;
	}

	TeleportTube->SetState(false);
	OtherActor->SetActorLocation(TeleportTube->GetActorLocation());
	State = false;
}

void ATube::OnBoxExitTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	State = true;
}