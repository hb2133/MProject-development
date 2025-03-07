// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MPWidget_CustomizeTooltip.generated.h"

class UMPWidgetSlot_PreviewItem;
class UMPWidgetSlot_CustomizeItem;
class UCSImage;
class UCSTextBlock;
class UCSButton;

UCLASS()
class MPROJECT_API UMPWidget_CustomizeTooltip : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* ButtonApply;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSImage* ImageApplyBtn;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSTextBlock* ItemInfoTextBlock;

	UPROPERTY()
	UMPWidgetSlot_CustomizeItem* CustomizeItem;
	UPROPERTY()
	UMPWidgetSlot_PreviewItem* PreviewItem;

public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	void SetPreviewItemInfo(UMPWidgetSlot_PreviewItem* pPreviewItemSlot);
	void SetCustomizeItemInfo(UMPWidgetSlot_CustomizeItem* pCustomizeItemSlot);
	
	UFUNCTION()
	void OnApplyButtonClicked();

private:
	bool m_bIsClickedPreviewItem;
};