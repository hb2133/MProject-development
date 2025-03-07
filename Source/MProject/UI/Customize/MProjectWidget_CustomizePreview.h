// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_CustomizePreview.generated.h"

class UMPWidget_PreviewItem;
class UCSButton;

UCLASS()
class MPROJECT_API UMProjectWidget_CustomizePreview : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* ButtonExit;

	UPROPERTY(meta = (BindWidgetOptional))
	UMPWidget_PreviewItem* PreviewItem;
	
public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) override {GetParentWidget()->OnChildItemClicked(_pChildWidget);}
	
	UFUNCTION()
	void OnExitButtonClicked();
};
