// Fill out your copyright notice in the Description page of Project Settings.

#include "MPWidgetSlot_CustomizeItem.h"
#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"
#include "MProject/DataTable/DataRecord/MPCustomizeRecord.h"
#include "MProject/Manager/MPCustomizeMgr.h"

#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"

void UMPWidgetSlot_CustomizeItem::InitData()
{
	Super::InitData();

	m_pSlotItemInfo = nullptr;
	
	SlotButton->SetTouchMethod(EButtonTouchMethod::Type::PreciseTap);
	SlotButton_Selected->SetTouchMethod(EButtonTouchMethod::Type::PreciseTap);
}

void UMPWidgetSlot_CustomizeItem::ReleaseData()
{
	Super::ReleaseData();
}

void UMPWidgetSlot_CustomizeItem::LinkEvent()
{
	Super::LinkEvent();
}

void UMPWidgetSlot_CustomizeItem::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMPWidgetSlot_CustomizeItem::SetSlotItemInfo(ItemInfo* slotItemInfo)
{
	if (slotItemInfo)
	{
		m_pSlotItemInfo = slotItemInfo;
		setSlotImage();
	}
}

void UMPWidgetSlot_CustomizeItem::setSlotImage()
{
	ItemImage->SetBrushFromSpriteName(m_pSlotItemInfo->strSpriteName);
		
	if (g_MPCustomizeSpriteRecordMgr)
	{
		FString strSpriteTid = "Item_Type_";
		strSpriteTid.Append(m_pSlotItemInfo->strItemType);
		FString strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
		SlotButton_Image_Icon->SetBrushFromSpriteName(strSpriteName);

		strSpriteTid.Append("_Equip");
		strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
		SlotButton_Image_Icon_Selected->SetBrushFromSpriteName(strSpriteName);
	}
}

void UMPWidgetSlot_CustomizeItem::SetIsWearing(bool isWearing)
{
	if (g_MPCustomizeMgrValid)
	{
		m_pSlotItemInfo->bIsWearing = isWearing;
		SetSelected(isWearing);
		g_MPCustomizeMgr->m_CustomizeItem[GetSlotIdx()]->m_pItemInfo->bIsWearing = isWearing;
	}
}
