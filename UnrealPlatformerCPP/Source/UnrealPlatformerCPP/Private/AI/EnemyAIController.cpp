#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/Enemy.h"

AEnemyAIController::AEnemyAIController()
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemy* Enemy = Cast<AEnemy>(InPawn);

	if (!Enemy || !Enemy->BehaviorTreeAsset)
	{
		return;
	}

	BBC->InitializeBlackboard(*Enemy->BehaviorTreeAsset->BlackboardAsset);
	TargetActor = BBC->GetKeyID(TargetActorName);

	RunBehaviorTree(Enemy->BehaviorTreeAsset);

	BTC->StartTree(*Enemy->BehaviorTreeAsset);
}
