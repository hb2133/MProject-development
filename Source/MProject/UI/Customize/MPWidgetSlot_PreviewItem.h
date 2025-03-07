// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSWidgetSlot.h"
#include "MPWidgetSlot_PreviewItem.generated.h"

class UCSWidgetSwitcher;
class UCSImage;
struct ItemInfo;

UCLASS()
class MPROJECT_API UMPWidgetSlot_PreviewItem : public UCSWidgetSlot
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSImage* ItemImage;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSWidgetSwitcher* ItemSwitcher;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSImage* UnequipImage;
	
public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	void SetSlotItemInfo(ItemInfo* slotItemInfo);
	ItemInfo* GetSlotItemInfo() const {return m_pSlotItemInfo;}
	
	void SetSlotBtnImage(const FString& slotBtnImage);

	void ShowUnequipImage();

private:
	ItemInfo* m_pSlotItemInfo;
};
