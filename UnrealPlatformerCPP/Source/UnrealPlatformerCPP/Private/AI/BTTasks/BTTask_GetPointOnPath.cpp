#include "AI/BTTasks/BTTask_GetPointOnPath.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AI/Enemy.h"
#include "Utility/SmartPath.h"

UBTTask_GetPointOnPath::UBTTask_GetPointOnPath()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Get Next Point on Path");
}

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

	if (PointIndex < PatrolPoints.Num() - 1)
	{
		PointIndex++;
	}
	else
	{
		PointIndex = 0;
	}

	return EBTNodeResult::Succeeded;
}