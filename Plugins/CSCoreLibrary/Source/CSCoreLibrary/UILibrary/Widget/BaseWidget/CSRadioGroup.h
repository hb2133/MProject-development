// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "CSCheckBox.h"
#include "CSRadioGroup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChildCheckStateChanged, UCSCheckBox*, CheckBox, ECheckBoxState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedIndexChanged, int, NewSelectedIndex);

UCLASS()
class CSCORELIBRARY_API UCSRadioGroup : public UCSCanvasPanel
{
	GENERATED_UCLASS_BODY()
public:
	
#if WITH_EDITOR
	// UWidget interface
	virtual bool LockToPanelOnDrag() const override
	{
		return true;
	}
	// End UWidget interface
#endif

	UFUNCTION()
	void SlateOnChildCheckStateChangedCallback(UCSCheckBox* checkBox, ECheckBoxState NewState);

	UPROPERTY(BlueprintAssignable, Category = "CheckBox|Event")
	FOnChildCheckStateChanged OnChildCheckStateChanged;

	FOnSelectedIndexChanged OnSelectedIndexChanged;

public:
	void SetChecked(int32 index, bool broadcast = false, bool allUnChecked = false);
	void SetChecked(UCSCheckBox* checkBox, bool broadcast = false, bool allUnChecked = false);

	int GetCheckedSlotIndex();
	UCSCheckBox* GetCheckedSlot();

	void AllUnChecked();
	int GetCheckedIndex();

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
};