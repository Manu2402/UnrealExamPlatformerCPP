#include "AI/BTTasks/BTTask_GetPointOnPath.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AI/Enemy.h"
#include "Utility/SmartPath.h"

UBTTask_GetPointOnPath::UBTTask_GetPointOnPath()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Get Next Point On Path");
}

/* I use a spline in order to create a path composed by flexable points. With this points i update the
blackboard with the current point position for the path. */
EBTNodeResult::Type UBTTask_GetPointOnPath::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	AAIController* EnemyAIController = OwnerComponent.GetAIOwner();
	AEnemy* Enemy = Cast<AEnemy>(EnemyAIController->GetPawn());

	if (!BlackboardComponent || !EnemyAIController || !Enemy)
	{
		return EBTNodeResult::Failed;
	}

	TArray<FVector> PatrolPoints = Enemy->PawnPath->GetSplinePoints();
	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(TargetPatrolLocationName, PatrolPoints[PointIndex]);

	PointIndex = (PointIndex + 1) % PatrolPoints.Num();

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}