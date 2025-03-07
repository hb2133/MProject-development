// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UILibrary/Widget/WidgetInterface/CSWidgetScrollBox.h"
#include "MPWidget_ScrollCustomizeItem.generated.h"

class UCSUniformGridPanel;

struct compareFName
{
	bool operator()(const FName& lhs, const FName& rhs) const
	{
		return lhs.Compare(rhs) <= 0;
	}
};

UCLASS()
class MPROJECT_API UMPWidget_ScrollCustomizeItem : public UCSWidgetScrollBox
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSUniformGridPanel* GridPanelCustomizeItem;
	
public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SynchronizeProperties() override;

	virtual void OnChildItemPressed(UCSUserWidgetBase* _pChildWidget) override;

	void InitCustomizeItemGridPanel();
	
	void SortCustomizeItemData();
	void SortCustomizeItemGridPanel();

private:
	std::multimap<FName, int32, compareFName> m_CustomizeItemData;
};
