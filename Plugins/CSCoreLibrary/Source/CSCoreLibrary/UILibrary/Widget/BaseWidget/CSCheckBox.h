// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CheckBox.h"
#include "CSCheckBox.generated.h"

class UCSWidgetSwitcher;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, UCSCheckBox*, CheckBox, ECheckBoxState, NewState);

UCLASS()
class CSCORELIBRARY_API UCSCheckBox : public UCheckBox
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "CSCheckBox", DisplayName = "CheckBoxType")
	FString m_strCheckBoxType;

protected:
	UCSWidgetSwitcher* m_widgetSwitcher;

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void PostLoad() override;
	void SetRadioGroupBroadcastCheckedState(ECheckBoxState NewState, bool Broadcast = false);
	void SetBroadcastCheckedState(ECheckBoxState NewState);

	void SetEnableMouseCapture(bool bValue);

public:
	/** Called when the checked state has changed */
	UPROPERTY(BlueprintAssignable, Category = "CheckBox|Event")
	FOnStateChanged OnStateChanged;

protected:
	void SlateOnStateChangedCallback(ECheckBoxState NewState);
	void UpdateSwitcher(ECheckBoxState newState);
};
