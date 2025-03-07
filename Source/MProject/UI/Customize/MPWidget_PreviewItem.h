// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/WidgetInterface/CSWidgetScrollBox.h"
#include "MPWidget_PreviewItem.generated.h"

class UCSUniformGridPanel;

UCLASS()
class MPROJECT_API UMPWidget_PreviewItem : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSUniformGridPanel* GridPanelPreviewItem;

public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) override { GetParentWidget()->OnChildItemClicked(_pChildWidget); }
	
private:
	void initPreviewItemGridPanel();
	void initPreviewItemSlot();
};
