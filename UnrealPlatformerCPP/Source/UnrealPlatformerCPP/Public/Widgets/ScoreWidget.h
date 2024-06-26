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

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	void SetScore(int32 Score);
	
};
