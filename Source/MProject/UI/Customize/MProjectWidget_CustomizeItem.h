// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_CustomizeItem.generated.h"

class UMPWidget_ScrollCustomizeItem;
class UMPWidget_ScrollCustomizeType;

UCLASS()
class MPROJECT_API UMProjectWidget_CustomizeItem : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UMPWidget_ScrollCustomizeItem* ScrollCustomizeItem;

	UPROPERTY(meta = (BindWidgetOptional))
	UMPWidget_ScrollCustomizeType* ScrollCustomizeType;
	
public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) override;

private:
	void initScrollCustomizeType();
};
