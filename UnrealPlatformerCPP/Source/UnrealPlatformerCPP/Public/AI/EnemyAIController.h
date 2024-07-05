#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	void SetActorValueIntoBlackboard(const FName& KeyName, AActor* Actor);

private:
	const FName& TargetActorName = TEXT("TargetActor");

	UPROPERTY()
	class UBehaviorTreeComponent* BTC;

	UPROPERTY()
	UBlackboardComponent* BBC;
	
};
