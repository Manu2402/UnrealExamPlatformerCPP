#include "AI/Enemy.h"
#include "Utility/SmartPath.h"
#include "Components/BoxComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollider"));

	if (DamageCollider)
	{
		DamageCollider->SetupAttachment(GetMesh(), DamageSocketString);
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}