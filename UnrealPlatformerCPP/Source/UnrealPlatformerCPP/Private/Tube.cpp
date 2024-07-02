#include "Tube.h"
#include "Components/BoxComponent.h"

ATube::ATube()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	TeleportTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveTrigger"));
	if (TeleportTrigger)
	{
		TeleportTrigger->SetBoxExtent(TriggerExtendParams);
		TeleportTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATube::OnBoxTriggered);
		TeleportTrigger->OnComponentEndOverlap.AddDynamic(this, &ATube::OnBoxExitTrigger);

		TeleportTrigger->SetupAttachment(RootComponent);
	}

	TubeMesh = LoadObject<UStaticMesh>(nullptr, TubeMeshPath);
	TubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TubeMeshComponent"));
	if (TubeMeshComponent)
	{
		TubeMeshComponent->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.5f));
		TubeMeshComponent->SetStaticMesh(TubeMesh);
		TubeMeshComponent->SetCollisionProfileName(NoCollisionPreset);

		TubeMeshComponent->SetupAttachment(RootComponent);
	}
}

void ATube::BeginPlay()
{
	Super::BeginPlay();

}

void ATube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATube::SetState(const bool Value)
{
	bIsActive = Value;
}

void ATube::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActive)
	{
		return;
	}

	if (!OtherActor->ActorHasTag(PlayerTag) || !TeleportTube)
	{
		return;
	}

	TeleportTube->SetState(false);
	OtherActor->SetActorLocation(TeleportTube->GetActorLocation());
	SetState(false);
}

void ATube::OnBoxExitTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetState(true);
}