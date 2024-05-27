#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotsWidget.generated.h"

UENUM()
enum ESlotsIndex : uint8
{
	Zero,
	One,
	Two
};

UCLASS()
class UNREALPLATFORMERCPP_API USlotsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Called when added to viewport.
	virtual void NativeConstruct() override;
	
private:
	const FName& MainLevelName = TEXT("Main");

	ESlotsIndex CurrentSlotIndex;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotZero;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotOne;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotTwo;

	UFUNCTION()
	void InitSlotZero();

	UFUNCTION()
	void InitSlotOne();

	UFUNCTION()
	void InitSlotTwo();

	void LoadLevel();
};
