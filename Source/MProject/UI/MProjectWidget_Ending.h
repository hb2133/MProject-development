// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_Ending.generated.h"

class UCSButton;
class UCSTextBlock;
UCLASS()
class MPROJECT_API UMProjectWidget_Ending : public UCSUserWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_End;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Rating;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Score;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Money;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Exp;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_AdMob;
	
protected:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	
private:
	UFUNCTION()
	void OnClick_End();

	UFUNCTION()
	void OnClick_AdMob();

	void SetResultText();
	FText GetDriggerRating(int32 remainingTime);
	FText GetDriggerMoney(int32 score);
	FText GetDriggerExp(int32 score);
	FText GetRunRating(int32 remainingTime, bool isClear);
	FText GetRunMoney(int32 score);
	FText GetRunExp(int32 score);
public:
	void UpdateRunResult(int32 isSeconds, bool isClear);
	void UpdateDriggerResult();
};
