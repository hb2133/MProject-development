// Fill out your copyright notice in the Description page of Project Settings.

#include "MPWidgetSlot_PreviewItem.h"

#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"
#include "MProject/DataTable/DataRecord/MPCustomizeRecord.h"

#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSWidgetSwitcher.h"

void UMPWidgetSlot_PreviewItem::InitData()
{
	Super::InitData();
	
	m_pSlotItemInfo = nullptr;
}

void UMPWidgetSlot_PreviewItem::ReleaseData()
{
	Super::ReleaseData();
}

void UMPWidgetSlot_PreviewItem::LinkEvent()
{
	Super::LinkEvent();
}

void UMPWidgetSlot_PreviewItem::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMPWidgetSlot_PreviewItem::SetSlotItemInfo(ItemInfo* slotItemInfo)
{
	if (slotItemInfo)
	{
		m_pSlotItemInfo = slotItemInfo;

		if (ItemSwitcher)
		{
			ItemSwitcher->SetActiveWidgetIndex(0);
			ItemImage->SetBrushFromSpriteName(m_pSlotItemInfo->strSpriteName);
			if (g_MPCustomizeSpriteRecordMgr)
			{
				FString strSpriteTid = "Item_Type_";
				strSpriteTid.Append(m_pSlotItemInfo->strItemType);
		
				FString strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
				SetSlotBtnImage(strSpriteName);
			}
		}
	}
}

void UMPWidgetSlot_PreviewItem::SetSlotBtnImage(const FString& slotBtnImage)
{
	SlotButton_Image_Icon->SetBrushFromSpriteName(slotBtnImage);
	SlotButton_Image_Icon_Selected->SetBrushFromSpriteName(slotBtnImage);
}

void UMPWidgetSlot_PreviewItem::ShowUnequipImage()
{
	SetSlotIdx(-1);
	ItemSwitcher->SetActiveWidgetIndex(1);
}
