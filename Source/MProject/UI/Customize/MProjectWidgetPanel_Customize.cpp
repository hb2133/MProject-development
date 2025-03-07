// Fill out your copyright notice in the Description page of Project Settings.

#include "MProjectWidgetPanel_Customize.h"
#include "MProjectWidget_CustomizePreview.h"
#include "MProjectWidget_CustomizeItem.h"
#include "MPWidgetSlot_CustomizeItem.h"
#include "MPWidgetSlot_PreviewItem.h"
#include "MPWidget_CustomizeTooltip.h"
#include "MPWidget_PreviewItem.h"
#include "MPWidget_ScrollCustomizeItem.h"
#include "NavigationSystem.h"
#include "MProject/Define/MPCustomizeCommon.h"
#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"

#include "CoreLibrary/Manager/CSFileManager.h"
#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSUniformGridPanel.h"
#include "UILibrary/Widget/BaseWidget/CSWidgetSwitcher.h"

void UMProjectWidgetPanel_Customize::InitData()
{
	Super::InitData();

	if (CustomizePreview)
	{
		CustomizePreview->SetParentWidget(this);
	}
	if (CustomizeItem)
	{
		CustomizeItem->SetParentWidget(this);
	}

	CustomizeTooltip = nullptr;
}

void UMProjectWidgetPanel_Customize::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidgetPanel_Customize::LinkEvent()
{
	Super::LinkEvent();
}

void UMProjectWidgetPanel_Customize::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMProjectWidgetPanel_Customize::OnChildItemClicked(UCSUserWidgetBase* _pChildWidget)
{
	Super::OnChildItemClicked(_pChildWidget);
	
	if (UMPWidgetSlot_CustomizeItem* pCustomizeItemSlot = Cast<UMPWidgetSlot_CustomizeItem>(_pChildWidget))
	{
		pCustomizeItemSlot->SetSelected(!pCustomizeItemSlot->GetSelected());
		setCustomizeTooltipWidget(pCustomizeItemSlot);
	}
	else if (UMPWidgetSlot_PreviewItem* pPreviewItemSlot = Cast<UMPWidgetSlot_PreviewItem>(_pChildWidget))
	{
		if (pPreviewItemSlot->GetSlotIdx() != -1)
		{
			setPreviewTooltipWidget(pPreviewItemSlot);
		}
	}
	else
	{
		if (CustomizeTooltip)
		{
			CustomizeTooltip->Hide();
		}
	}
}

void UMProjectWidgetPanel_Customize::OnTooltipBtnClicked(bool isClickedPreviewItem)
{
	if (isClickedPreviewItem)
	{
		UMPWidgetSlot_PreviewItem* pSelectedPreviewItemSlot = CustomizeTooltip->PreviewItem;
		int32 previewSlotIdx = pSelectedPreviewItemSlot->GetSlotIdx();
		
		if (UMPWidgetSlot_CustomizeItem* pCustomizeItemSlot =
			Cast<UMPWidgetSlot_CustomizeItem>(CustomizeItem->ScrollCustomizeItem->GridPanelCustomizeItem->GetChildAt(previewSlotIdx)))
		{
			pCustomizeItemSlot->SetIsWearing(false);
			
			pSelectedPreviewItemSlot->ShowUnequipImage();
		}
	}
	else
	{
		UMPWidgetSlot_CustomizeItem* pSelectedCustomizeItemSlot = CustomizeTooltip->CustomizeItem;
		if (UMPWidgetSlot_PreviewItem* pPreviewItemSlot =
				Cast<UMPWidgetSlot_PreviewItem>(CustomizePreview->PreviewItem->GridPanelPreviewItem->GetChildAt(
					nCustomType::GetEnum(pSelectedCustomizeItemSlot->GetSlotItemInfo()->strCustomType, false))))
		{
			if (pSelectedCustomizeItemSlot->GetSlotItemInfo()->bIsWearing)
			{
				pPreviewItemSlot->ShowUnequipImage();
				
				pSelectedCustomizeItemSlot->SetIsWearing(false);
			}
			else
			{
				int32 preCustomizeItemSlotIdx = pPreviewItemSlot->GetSlotIdx();
				if (UMPWidgetSlot_CustomizeItem* pPreCustomizeItemSlot =
					Cast<UMPWidgetSlot_CustomizeItem>(CustomizeItem->ScrollCustomizeItem->GridPanelCustomizeItem->GetChildAt(preCustomizeItemSlotIdx)))
				{
					pPreCustomizeItemSlot->SetIsWearing(false);
						
				}
				pSelectedCustomizeItemSlot->SetIsWearing(true);
						
				pPreviewItemSlot->SetSlotIdx(pSelectedCustomizeItemSlot->GetSlotIdx());
				pPreviewItemSlot->SetSlotItemInfo(pSelectedCustomizeItemSlot->GetSlotItemInfo());
			}
		}
	}

	CustomizeItem->ScrollCustomizeItem->SortCustomizeItemData();
	CustomizeItem->ScrollCustomizeItem->SortCustomizeItemGridPanel();
}

void UMProjectWidgetPanel_Customize::setPreviewTooltipWidget(UMPWidgetSlot_PreviewItem* previewItemSlot)
{
	if (!CustomizeTooltip)
	{
		if(UClass* slotClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass,"W_CustomizeTooltip_BP"))
		{
			CustomizeTooltip = CreateWidget<UMPWidget_CustomizeTooltip>(this, slotClass);
			CustomizeTooltip->SetParentWidget(this);
			
			CustomizeTooltip->AddToViewport(5);
			CustomizeTooltip->Hide();
		}
	}

	CustomizeTooltip->SetPreviewItemInfo(previewItemSlot);
	CustomizeTooltip->Show();
}

void UMProjectWidgetPanel_Customize::setCustomizeTooltipWidget(UMPWidgetSlot_CustomizeItem* customizeItemSlot)
{
	if (!CustomizeTooltip)
	{
		if(UClass* slotClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass,"W_CustomizeTooltip_BP"))
		{
			CustomizeTooltip = CreateWidget<UMPWidget_CustomizeTooltip>(this, slotClass);
			CustomizeTooltip->SetParentWidget(this);
			
			CustomizeTooltip->AddToViewport(5);
			CustomizeTooltip->Hide();
		}
	}

	CustomizeTooltip->SetCustomizeItemInfo(customizeItemSlot);
	CustomizeTooltip->Show();
}