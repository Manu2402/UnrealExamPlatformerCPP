#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Patrol.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UBTTask_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Patrol();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime) override;

private:
	const FName& TargetPatrolLocationName = TEXT("TargetPatrolLocation");

	bool HasReachedTarget(const APawn* Enemy, const FVector& TargetLocation, const float& AcceptanceRadius);

};
