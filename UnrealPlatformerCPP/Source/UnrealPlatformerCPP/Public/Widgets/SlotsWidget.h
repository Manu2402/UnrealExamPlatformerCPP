#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotsWidget.generated.h"

UCLASS()
class UNREALPLATFORMERCPP_API USlotsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	class UPlatformerGameInstance* PlatformerGameInstance;

	UWorld* World = GetWorld();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotZero;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotOne;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotTwo;
	
	void LoadLevel() const;

	UFUNCTION()
	void InitSlotZero();

	UFUNCTION()
	void InitSlotOne();

	UFUNCTION()
	void InitSlotTwo();

};
