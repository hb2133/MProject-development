// Fill out your copyright notice in the Description page of Project Settings.

#include "MPWidget_PreviewItem.h"

#include "MPWidgetSlot_PreviewItem.h"
#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"
#include "MProject/DataTable/DataRecord/MPCustomizeRecord.h"
#include "MProject/Manager/MPCustomizeMgr.h"

#include "Components/UniformGridSlot.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"
#include "UILibrary/Manager/CSGameMsgMgr.h"
#include "UILibrary/Widget/CSUIUtils.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSUniformGridPanel.h"


void UMPWidget_PreviewItem::InitData()
{
	Super::InitData();

	initPreviewItemGridPanel();
	initPreviewItemSlot();
}

void UMPWidget_PreviewItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMPWidget_PreviewItem::LinkEvent()
{
	Super::LinkEvent();
}

void UMPWidget_PreviewItem::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMPWidget_PreviewItem::initPreviewItemGridPanel()
{
	for (int32 customizeItemType = 0; customizeItemType < nCustomType::Max; customizeItemType++)
	{
		if(UClass* slotClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass,"S_PreviewItem_BP"))
		{
			if(UMPWidgetSlot_PreviewItem* pSlot = CreateWidget<UMPWidgetSlot_PreviewItem>(this, slotClass))
			{
				if(GridPanelPreviewItem)
				{
					GridPanelPreviewItem->AddChild(pSlot);
					if(UUniformGridSlot* pGridSlot = Cast<UUniformGridSlot>(pSlot->Slot))
					{
						pGridSlot->SetColumn((customizeItemType & 1) * 3);
						pGridSlot->SetRow(customizeItemType >> 1);
					}
					
					if (g_MPCustomizeSpriteRecordMgr)
					{
						FString strSpriteTid = "Slot_Type_";
						if (customizeItemType == nCustomType::Chest || customizeItemType == nCustomType::Pants)
						{
							strSpriteTid += "Dress";
						}
						else if (customizeItemType == nCustomType::Bag)
						{
							strSpriteTid += "Bag";
						}
						else
						{
							strSpriteTid += "Tool";
						}
						FString strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
						pSlot->UnequipImage->SetBrushFromSpriteName(strSpriteName);
						
						pSlot->ShowUnequipImage();
						pSlot->SetClickEvent(this);
					}
				}
			}
		}
	}
}

void UMPWidget_PreviewItem::initPreviewItemSlot()
{
	if (g_MPCustomizeMgrValid)
	{
		TArray<MPCustomizeRecord*> customizeRecords = g_MPCustomizeMgr->m_CustomizeItem;
		for (int32 customizeRecordIndex = 0; customizeRecordIndex < customizeRecords.Num(); customizeRecordIndex++)
		{
			if (ItemInfo* pSlotItemInfo = customizeRecords[customizeRecordIndex]->m_pItemInfo)
			{
				if (pSlotItemInfo->bIsWearing)
				{
					if (UMPWidgetSlot_PreviewItem* pSlot =
						Cast<UMPWidgetSlot_PreviewItem>(GridPanelPreviewItem->GetChildAt(nCustomType::GetEnum(pSlotItemInfo->strCustomType, false))))
					{
						pSlot->SetSlotItemInfo(customizeRecords[customizeRecordIndex]->m_pItemInfo);
						pSlot->SetSlotIdx(customizeRecordIndex);
					}
				}
			}
		}
	}
}
