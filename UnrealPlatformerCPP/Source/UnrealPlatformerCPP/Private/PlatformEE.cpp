#include "PlatformEE.h"
#include "Components/BoxComponent.h"

APlatformEE::APlatformEE()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollider"));
	if (TriggerCollider)
	{
		TriggerCollider->SetBoxExtent(TriggerExtendParams);
		TriggerCollider->SetRelativeLocation(TriggerLocation);
		TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &APlatformEE::OnBoxTriggered);

		TriggerCollider->SetupAttachment(RootComponent);
		TriggerCollider->bHiddenInGame = false;
	}

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	if (PlatformMeshComponent)
	{
		UStaticMesh* PlatformMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
		if (PlatformMesh)
		{
			UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Materials/M_Gray.M_Gray"));
			if (Material)
			{
				PlatformMeshComponent->SetStaticMesh(PlatformMesh);
				PlatformMeshComponent->SetWorldScale3D(MeshScaleParams);

				PlatformMesh->SetMaterial(0, Material);
				PlatformMeshComponent->SetupAttachment(RootComponent);
			}
		}
	}
}

void APlatformEE::BeginPlay()
{
	Super::BeginPlay();

}

void APlatformEE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformEE::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("SAS"));
}
