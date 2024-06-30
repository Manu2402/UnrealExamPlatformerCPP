#include "PlatformEE.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacterState.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"

APlatformEE::APlatformEE()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("MovementIgnored");

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
	if (!bIsActive)
	{
		return;
	}

	bIsActive = false;
	ToggleScore(666);
}

void APlatformEE::ToggleScore(int32 Score)
{
	APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (PlayerCharacterState)
	{
		PlayerCharacterState->SetCurrentScore(Score);

		ULevel* CurrentLevel = GetWorld()->GetCurrentLevel();
		if (CurrentLevel)
		{
			AMainLevelScriptActor* MainLevelScriptActor = Cast<AMainLevelScriptActor>(CurrentLevel->GetLevelScriptActor());
			if (MainLevelScriptActor)
			{
				MainLevelScriptActor->SetScoreOnUI(PlayerCharacterState->GetCurrentScore());
			}
		}
	}

	// Apply Post processing red tint into camera.
}
