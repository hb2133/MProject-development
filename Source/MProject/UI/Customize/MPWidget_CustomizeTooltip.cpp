// Fill out your copyright notice in the Description page of Project Settings.


#include "MPWidget_CustomizeTooltip.h"
#include "MProjectWidgetPanel_Customize.h"
#include "MPWidgetSlot_CustomizeItem.h"
#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"
#include "MProject/Define/MPCustomizeCommon.h"
#include "MPWidgetSlot_PreviewItem.h"

#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"

void UMPWidget_CustomizeTooltip::InitData()
{
	Super::InitData();

	CustomizeItem = nullptr;
	PreviewItem = nullptr;
	m_bIsClickedPreviewItem = false;
}

void UMPWidget_CustomizeTooltip::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMPWidget_CustomizeTooltip::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(ButtonApply, &UMPWidget_CustomizeTooltip::OnApplyButtonClicked);
}

void UMPWidget_CustomizeTooltip::UnLinkEvent()
{
	UNBIND_BUTTON_EVENT_ALL(ButtonApply);
	
	Super::UnLinkEvent();
}

void UMPWidget_CustomizeTooltip::SetPreviewItemInfo(UMPWidgetSlot_PreviewItem* pPreviewItemSlot)
{
	if (pPreviewItemSlot)
	{
		PreviewItem = pPreviewItemSlot;
		
		FString itemInfoText = "Item Name: " + pPreviewItemSlot->GetSlotItemInfo()->strSpriteName;
		itemInfoText += "\nItem Type: " + pPreviewItemSlot->GetSlotItemInfo()->strItemType;
		itemInfoText += "\nItem Custom Type: " + pPreviewItemSlot->GetSlotItemInfo()->strCustomType;
		ItemInfoTextBlock->SetText(FText::FromString(itemInfoText));
        
		if (g_MPCustomizeSpriteRecordMgr)
		{
			FString strSpriteTid = "Btn_Tooltip_UnEquip";
			FString strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
			ImageApplyBtn->SetBrushFromSpriteName(strSpriteName);
		}

		m_bIsClickedPreviewItem = true;
	}
}

void UMPWidget_CustomizeTooltip::SetCustomizeItemInfo(UMPWidgetSlot_CustomizeItem* pCustomizeItemSlot)
{
	if (pCustomizeItemSlot)
	{
		CustomizeItem = pCustomizeItemSlot;
		
		FString strItemInfoText = "Item Name: " + pCustomizeItemSlot->GetSlotItemInfo()->strSpriteName;
		strItemInfoText += "\nItem Type: " + pCustomizeItemSlot->GetSlotItemInfo()->strItemType;
		strItemInfoText += "\nItem Custom Type: " + pCustomizeItemSlot->GetSlotItemInfo()->strCustomType;
		ItemInfoTextBlock->SetText(FText::FromString(strItemInfoText));
        
		if (g_MPCustomizeSpriteRecordMgr)
		{
			FString strSpriteTid = "Btn_Tooltip_";
			if (pCustomizeItemSlot->GetSlotItemInfo()->bIsWearing)
			{
				strSpriteTid.Append("Unequip");
			}
			else
			{
				strSpriteTid.Append("Equip");
			}
			
			FString strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
			ImageApplyBtn->SetBrushFromSpriteName(strSpriteName);
		}

		m_bIsClickedPreviewItem = false;
	}
}

void UMPWidget_CustomizeTooltip::OnApplyButtonClicked()
{
	Hide();

	if (UMProjectWidgetPanel_Customize* pPanelCustomize = Cast<UMProjectWidgetPanel_Customize>(GetParentWidget()))
	{
		pPanelCustomize->OnTooltipBtnClicked(m_bIsClickedPreviewItem);
	}
}
