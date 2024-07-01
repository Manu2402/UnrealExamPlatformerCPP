#include "Utility/FlagPole.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterState.h"

AFlagPole::AFlagPole()
{
	PrimaryActorTick.bCanEverTick = true;

	FlagPoleMaterials.Add(0, MaterialPath);
	FlagPoleMaterials.Add(1, PipeMaterialPath);
	FlagPoleMaterials.Add(2, YellowBallMaterialPath);
	FlagPoleMaterials.Add(3, FlagMaterialPath);
	FlagPoleMaterials.Add(4, BrickMaterialPath);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollider"));
	if (TriggerCollider)
	{
		TriggerCollider->SetBoxExtent(TriggerExtendParams);
		TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &AFlagPole::OnBoxTriggered);

		TriggerCollider->SetupAttachment(RootComponent);
	}

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	if (FlagMesh)
	{
		UStaticMesh* Flag = LoadObject<UStaticMesh>(nullptr, FlagPoleMeshPath);
		if (!Flag)
		{
			return;
		}

		FlagMesh->SetStaticMesh(Flag);

		FlagMesh->SetupAttachment(RootComponent);

		FlagMesh->SetRelativeLocation(FlagMeshLocation);
		FlagMesh->SetRelativeScale3D(FlagMeshScale);

		SetMaterials();

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
	UWorld* World = GetWorld();
	// Controllare se è il best score e salvarlo in caso
	APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	UPlatformerGameInstance* PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(World));

	if (!PlatformerGameInstance)
	{
		return;
	}

	// Handling end game and best score.
	if (PlayerCharacterState)
	{
		if (PlayerCharacterState->GetCurrentScore() > PlayerCharacterState->GetBestScore())
		{
			PlayerCharacterState->SetBestScore(PlayerCharacterState->GetCurrentScore());
			PlatformerGameInstance->SaveBestScore(World, 0);

			AMainLevelScriptActor* MainLevelScriptActor = Cast<AMainLevelScriptActor>(World->GetLevelScriptActor());
			if (MainLevelScriptActor)
			{
				MainLevelScriptActor->SetBestScoreOnUI(PlayerCharacterState->GetBestScore());
			}
		}

		PlatformerGameInstance->EndGame(UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex()), 0);
	}
}

void AFlagPole::SetMaterials() const
{
	// "auto" keyword is similar to "var" in C# (for this use, sure is more complicated than this).
	for (auto& FlagPoleMaterial : FlagPoleMaterials)
	{
		// Setting all materials.
		UMaterial* Material = LoadObject<UMaterial>(nullptr, FlagPoleMaterial.Value);
		FlagMesh->SetMaterial(FlagPoleMaterial.Key, Material);
	}
}