// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_DriggerCount.generated.h"

class UCSImage;
class UCSTextBlock;
UCLASS()
class MPROJECT_API UMProjectWidget_DriggerCount : public UCSUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

public:
	void SetBlockOneCount(int32 HealthCount);
	void SetBlockTwoCount(int32 HealthCount);
	void SetBlockThreeCount(int32 HealthCount);
	
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_BackGround;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Count;
};
