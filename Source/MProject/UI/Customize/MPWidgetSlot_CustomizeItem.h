// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSWidgetSlot.h"
#include "MPWidgetSlot_CustomizeItem.generated.h"

class UCSImage;
struct ItemInfo;

UCLASS()
class MPROJECT_API UMPWidgetSlot_CustomizeItem : public UCSWidgetSlot
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSImage* ItemImage;
	
public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	void SetSlotItemInfo(ItemInfo* slotItemInfo);
	void SetIsWearing(bool isWearing);
	
	ItemInfo* GetSlotItemInfo() const {return m_pSlotItemInfo;}

private:
	void setSlotImage();

private:
	ItemInfo* m_pSlotItemInfo;
};