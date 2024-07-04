#include "AI/Enemy.h"
#include "Utility/SmartPath.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacterState.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/LevelScriptsActor/MainLevelScriptActor.h"
#include "Utility/Subsystems/PlatformerGameInstance.h"
#include "Utility/Subsystems/TubeManagerSubsystem.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(EnemyTag);

	DamageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollider"));

	if (DamageCollider)
	{
		DamageCollider->SetupAttachment(GetMesh(), DamageSocketString);
		DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBoxTriggered);
		DamageCollider->SetBoxExtent(DamageColliderExtent);

		DamageCollider->bHiddenInGame = false;
	}

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	PlatformerGameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(World));
	TubeManager = PlatformerGameInstance->GetSubsystem<UTubeManagerSubsystem>();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnBoxTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(PlayerTag))
	{
		return;
	}

	bIsActive = false;
	EnableEnemy(bIsActive);
	TubeManager->ToggleTubeQuestState(FirstFloorQuestString, !bIsActive);
}

void AEnemy::EnableEnemy(const bool bValue)
{
	SetActorHiddenInGame(!bValue);
	SetActorEnableCollision(bValue);
	SetActorTickEnabled(bValue);
}

bool AEnemy::GetEnemyIsActive() const
{
	return bIsActive;
}

void AEnemy::SetEnemyIsActive(bool bIsEnemyActive)
{
	bIsActive = bIsEnemyActive;
	EnableEnemy(bIsActive);
}

void AEnemy::ToggleScore(const int32& Score)
{
	PlayerCharacterState = Cast<APlayerCharacterState>(UGameplayStatics::GetPlayerState(World, 0));
	if (!PlayerCharacterState)
	{
		return;
	}

	PlayerCharacterState->RemoveScore(Score);
	if (PlayerCharacterState->Losing())
	{
		if (PlatformerGameInstance)
		{
			PlatformerGameInstance->EndGame(UEnum::GetValueAsString(PlatformerGameInstance->GetCurrentSlotIndex()), 0);
		}

		return;
	}

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
}