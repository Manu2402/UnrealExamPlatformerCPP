#include "PlatformEE.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"

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
	}

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	if (!PlatformMeshComponent)
	{
		return;
	}

	UStaticMesh* PlatformMesh = LoadObject<UStaticMesh>(nullptr, CubeMeshPath);
	if (!PlatformMesh)
	{
		return;
	}

	UMaterial* Material = LoadObject<UMaterial>(nullptr, GrayMaterialPath);
	if (!Material)
	{
		return;
	}

	PlatformMeshComponent->SetStaticMesh(PlatformMesh);
	PlatformMeshComponent->SetWorldScale3D(MeshScaleParams);

	PlatformMesh->SetMaterial(0, Material);

	PlatformMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlatformMeshComponent->SetupAttachment(RootComponent);
}

void APlatformEE::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
}

void APlatformEE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlatformEE::GetIsActive() const
{
	return bIsActive;
}

void APlatformEE::SetIsActive(bool bValue)
{
	bIsActive = bValue;
}

void APlatformEE::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActive)
	{
		return;
	}

	bIsActive = false;
	ToggleScore(PlatformEEScore);
}

void APlatformEE::ToggleScore(const int32& Score)
{
	PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return;
	}

	PlayerCharacterState->SetCurrentScore(Score);

	CurrentLevel = World->GetCurrentLevel();
	if (!CurrentLevel)
	{
		return;
	}

	MainLevelScriptActor = Cast<AMainLevelScriptActor>(CurrentLevel->GetLevelScriptActor());
	if (!MainLevelScriptActor)
	{
		return;
	}

	MainLevelScriptActor->SetScoreOnUI(PlayerCharacterState->GetCurrentScore());

	// Apply Post processing red tint into camera.
	MainLevelScriptActor->SetPPWeight(1);

	MakeNoise();
}

void APlatformEE::MakeNoise() const
{
	FSoftObjectPath SoundAssetPath(JumpscareCuePath);
	USoundBase* JumpscareSound = Cast<USoundBase>(SoundAssetPath.TryLoad());
	if (!JumpscareSound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpscareSound, GetActorLocation());
}
