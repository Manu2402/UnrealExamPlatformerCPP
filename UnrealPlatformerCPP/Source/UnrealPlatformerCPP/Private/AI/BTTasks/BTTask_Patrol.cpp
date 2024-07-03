#include "AI/BTTasks/BTTask_Patrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AI/Enemy.h"
#include "Utility/SmartPath.h"
#include "NavigationSystem.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	AAIController* EnemyAIController = OwnerComponent.GetAIOwner();
	AEnemy* Enemy = Cast<AEnemy>(EnemyAIController->GetPawn());

	if (!BlackboardComponent || !EnemyAIController || !Enemy)
	{
		return EBTNodeResult::Failed;
	}

	FVector PatrolLocation = BlackboardComponent->GetValueAsVector(TargetPatrolLocationName);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		EnemyAIController->MoveToLocation(PatrolLocation);
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComponent, NodeMemory, DeltaTime);

	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	AAIController* EnemyAIController = OwnerComponent.GetAIOwner();
	AEnemy* Enemy = Cast<AEnemy>(EnemyAIController->GetPawn());

	if (!BlackboardComponent || !EnemyAIController || !Enemy)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
	}

	FVector PatrolLocation = BlackboardComponent->GetValueAsVector(TargetPatrolLocationName);

	if (HasReachedTarget(Enemy, PatrolLocation, 100))
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	}

}

bool UBTTask_Patrol::HasReachedTarget(const AEnemy* Enemy, const FVector& PatrolLocation, const float AcceptanceRadius)
{
	FVector EnemyLocation = Enemy->GetActorLocation();
	return FVector::Distance(EnemyLocation, PatrolLocation) < AcceptanceRadius;
}