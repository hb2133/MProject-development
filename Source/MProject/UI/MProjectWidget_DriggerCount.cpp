// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidget_DriggerCount.h"

#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"

void UMProjectWidget_DriggerCount::InitData()
{
	Super::InitData();
}

void UMProjectWidget_DriggerCount::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidget_DriggerCount::LinkEvent()
{
	Super::LinkEvent();
}

void UMProjectWidget_DriggerCount::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMProjectWidget_DriggerCount::SetBlockOneCount(int32 HealthCount)
{
	Image_BackGround->SetBrushFromSpriteName("SPR_Count1_Image");
	TextBlock_Count->SetText(FText::AsNumber(HealthCount));
}

void UMProjectWidget_DriggerCount::SetBlockTwoCount(int32 HealthCount)
{
	Image_BackGround->SetBrushFromSpriteName("SPR_Count2_Image");
	TextBlock_Count->SetText(FText::AsNumber(HealthCount));
}
void UMProjectWidget_DriggerCount::SetBlockThreeCount(int32 HealthCount)
{
	Image_BackGround->SetBrushFromSpriteName("SPR_Count3_Image");
	TextBlock_Count->SetText(FText::AsNumber(HealthCount));
}