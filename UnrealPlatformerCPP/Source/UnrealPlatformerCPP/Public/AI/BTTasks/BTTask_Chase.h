#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Chase.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UBTTask_Chase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Chase();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime) override;

private:
	const FName& TargetActorName = TEXT("TargetActor");
	const float& AcceptanceRadius = 100;

	bool HasReachedTarget(const class AEnemy* Enemy, const FVector& ActorLocation, const float& AcceptanceRadiusParam);

};
