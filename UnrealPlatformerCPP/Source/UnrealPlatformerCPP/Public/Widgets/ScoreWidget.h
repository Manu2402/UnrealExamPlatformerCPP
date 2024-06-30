#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Called when added to viewport.
	virtual void NativeConstruct() override;

public:
	void SetScore(int32 Score);
	void SetBestScore(int32 Score);

private:
	const FText& VoidBestScore = FText::FromString(TEXT("###"));

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* BestScoreText;
	
};
