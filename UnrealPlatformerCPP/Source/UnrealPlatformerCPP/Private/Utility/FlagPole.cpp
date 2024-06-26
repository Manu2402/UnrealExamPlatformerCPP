#include "Utility/FlagPole.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

AFlagPole::AFlagPole()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollider"));
	if (TriggerCollider)
	{
		TriggerCollider->SetBoxExtent(TriggerExtendParams);
		TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &AFlagPole::OnBoxTriggered);

		TriggerCollider->SetupAttachment(RootComponent);
		TriggerCollider->bHiddenInGame = false;
	}

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	if (FlagMesh)
	{
		UStaticMesh* Flag = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Custom/Meshes/Flags/FlagPole/SM_FlagPole.SM_FlagPole"));
		FlagMesh->SetStaticMesh(Flag);

		FlagMesh->SetupAttachment(RootComponent);

		FlagMesh->SetRelativeLocation(FlagMeshLocation);
		FlagMesh->SetRelativeScale3D(FlagMeshScale);

		UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Meshes/Flags/FlagPole/Material.Material"));
		FlagMesh->SetMaterial(0, Material);
		Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Meshes/Flags/FlagPole/Pipe.Pipe"));
		FlagMesh->SetMaterial(1, Material);
		Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Meshes/Flags/FlagPole/Yellow_ball.Yellow_ball"));
		FlagMesh->SetMaterial(2, Material);
		Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Meshes/Flags/FlagPole/Flag.Flag"));
		FlagMesh->SetMaterial(3, Material);
		Material = LoadObject<UMaterial>(nullptr, TEXT("/Game/Custom/Meshes/Flags/FlagPole/Brick.Brick"));
		FlagMesh->SetMaterial(4, Material);

		FlagMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AFlagPole::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlagPole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlagPole::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(GetWorld(), SlotsLevelName);
}