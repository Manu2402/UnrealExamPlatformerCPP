#include "AI/BTTasks/BTTask_Chase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "AI/Enemy.h"
#include "NavigationSystem.h"
#include "AI/EnemyAIController.h"

UBTTask_Chase::UBTTask_Chase()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	NodeName = TEXT("Chase");
}

/* Getting target location, where target is the player, and move towards it. Repeated even in tick task,
otherwise the method ends chase task at the first frame. */
EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComponent.GetAIOwner());
	AEnemy* Enemy = Cast<AEnemy>(EnemyAIController->GetPawn());

	Enemy->SetMaxWalkSpeed(Enemy->ChaseSpeed);

	if (!BlackboardComponent || !EnemyAIController || !Enemy)
	{
		return EBTNodeResult::Failed;
	}

	UObject* TargetObject = BlackboardComponent->GetValueAsObject(TargetActorName);
	if (!TargetObject)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(TargetObject);
	if (!TargetActor)
	{
		return EBTNodeResult::Failed;
	}

	FVector TargetActorLocation = TargetActor->GetActorLocation();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		EnemyAIController->MoveToLocation(TargetActorLocation);
		return EBTNodeResult::InProgress;
	}

	BlackboardComponent->SetValueAsObject(TargetActorName, nullptr);
	return EBTNodeResult::Failed;
}

void UBTTask_Chase::TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComponent, NodeMemory, DeltaTime);

	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComponent.GetAIOwner());
	AEnemy* Enemy = Cast<AEnemy>(EnemyAIController->GetPawn());

	if (!BlackboardComponent || !EnemyAIController || !Enemy)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return;
	}

	UObject* TargetObject = BlackboardComponent->GetValueAsObject(TargetActorName);
	if (!TargetObject)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return;
	}

	AActor* TargetActor = Cast<AActor>(TargetObject);
	if (!TargetActor)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return;
	}

	FVector TargetActorLocation = TargetActor->GetActorLocation();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return;
	}

	if (HasReachedTarget(Enemy, TargetActorLocation, AcceptanceRadius))
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return;
	}

	EnemyAIController->MoveToLocation(TargetActorLocation);
	FinishLatentTask(OwnerComponent, EBTNodeResult::InProgress);
}

bool UBTTask_Chase::HasReachedTarget(const AEnemy* Enemy, const FVector& ActorLocation, const float& AcceptanceRadiusParam)
{
	FVector EnemyLocation = Enemy->GetActorLocation();
	return FVector::Distance(EnemyLocation, ActorLocation) < AcceptanceRadiusParam;
}