#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetScore(const int32 Score);
	void SetBestScore(const int32 Score);

private:
	UWorld* World = GetWorld();

	const FText& VoidBestScore = FText::FromString(TEXT("###"));

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* BestScoreText;
	
};
