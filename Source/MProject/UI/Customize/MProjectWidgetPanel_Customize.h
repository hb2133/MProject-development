// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSWidgetPanel.h"
#include "MProjectWidgetPanel_Customize.generated.h"

class UMProjectWidget_CustomizePreview;
class UMProjectWidget_CustomizeItem;
class UMPWidget_CustomizeTooltip;
class UMPWidgetSlot_CustomizeItem;
class UMPWidgetSlot_PreviewItem;

UCLASS()
class MPROJECT_API UMProjectWidgetPanel_Customize : public UCSWidgetPanel
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UMProjectWidget_CustomizePreview* CustomizePreview;

	UPROPERTY(meta = (BindWidgetOptional))
	UMProjectWidget_CustomizeItem* CustomizeItem;

	UPROPERTY(meta = (BindWidgetOptional))
	UMPWidget_CustomizeTooltip* CustomizeTooltip;
	
public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) override;

	void OnTooltipBtnClicked(bool isClickedPreviewItem);
	
private:
	void setPreviewTooltipWidget(UMPWidgetSlot_PreviewItem* previewItemSlot);
	void setCustomizeTooltipWidget(UMPWidgetSlot_CustomizeItem* customizeItemSlot);
};
