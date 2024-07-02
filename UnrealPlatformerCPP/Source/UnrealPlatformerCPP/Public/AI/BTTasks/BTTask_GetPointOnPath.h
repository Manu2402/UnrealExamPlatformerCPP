#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPointOnPath.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UBTTask_GetPointOnPath : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_GetPointOnPath();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

protected:
	const FName& TargetPatrolLocationName = TEXT("TargetPatrolLocation");

	int32 PointIndex = 0;
};
