// Fill out your copyright notice in the Description page of Project Settings.


#include "MPWidget_ScrollCustomizeItem.h"
#include "MPWidgetSlot_CustomizeItem.h"
#include "MPWidget_CustomizeTooltip.h"
#include "Components/CanvasPanelSlot.h"
#include "MProject/Manager/MPCustomizeMgr.h"
#include "MProject/DataTable/DataRecord/MPCustomizeRecord.h"

#include "Components/UniformGridSlot.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSScrollBox.h"
#include "UILibrary/Widget/BaseWidget/CSUniformGridPanel.h"

void UMPWidget_ScrollCustomizeItem::InitData()
{
	Super::InitData();

	InitCustomizeItemGridPanel();
	SortCustomizeItemData();
	SortCustomizeItemGridPanel();
}

void UMPWidget_ScrollCustomizeItem::ReleaseData()
{
	Super::ReleaseData();
}

void UMPWidget_ScrollCustomizeItem::LinkEvent()
{
	Super::LinkEvent();
}

void UMPWidget_ScrollCustomizeItem::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMPWidget_ScrollCustomizeItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMPWidget_ScrollCustomizeItem::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UMPWidget_ScrollCustomizeItem::OnChildItemPressed(UCSUserWidgetBase* _pChildWidget)
{
	Super::OnChildItemPressed(_pChildWidget);
	
	if (UMPWidgetSlot_CustomizeItem* pPressedItem = Cast<UMPWidgetSlot_CustomizeItem>(_pChildWidget))
	{
		pPressedItem->SlotButton->OnReleased.Broadcast();
		pPressedItem->SlotButton_Selected->OnReleased.Broadcast();
	}
}

void UMPWidget_ScrollCustomizeItem::InitCustomizeItemGridPanel()
{
	if (g_MPCustomizeMgrValid)
	{
		int32 columnMax = g_MPCustomizeMgr->m_ColumnMax;
		if (columnMax > 0)
		{
			if (GridPanelCustomizeItem)
			{
				if(UClass* slotClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass,"S_CustomizeItem_BP"))
				{
					TArray<MPCustomizeRecord*> customizeRecords = g_MPCustomizeMgr->m_CustomizeItem;
					for (int32 customizeRecordIndex = 0; customizeRecordIndex < customizeRecords.Num(); customizeRecordIndex++)
					{
						if(UMPWidgetSlot_CustomizeItem* pSlot = CreateWidget<UMPWidgetSlot_CustomizeItem>(this, slotClass))
						{
							GridPanelCustomizeItem->AddChild(pSlot);

							if(UUniformGridSlot* pGridSlot = Cast<UUniformGridSlot>(pSlot->Slot))
							{
								pGridSlot->SetColumn(customizeRecordIndex % columnMax);
								pGridSlot->SetRow(customizeRecordIndex / columnMax);
							}
								
							pSlot->SetSlotItemInfo(customizeRecords[customizeRecordIndex]->m_pItemInfo);
							pSlot->SetSlotIdx(customizeRecordIndex);
							pSlot->SetClickEvent(this);
							pSlot->SetSelected(pSlot->GetSlotItemInfo()->bIsWearing);
						}
					}
				}
			}
		}
	}
}

void UMPWidget_ScrollCustomizeItem::SortCustomizeItemData()
{
	if (g_MPCustomizeMgrValid)
	{
		if (!m_CustomizeItemData.empty())
		{
			m_CustomizeItemData.clear();
		}
		
		TArray<MPCustomizeRecord*> customizeRecords = g_MPCustomizeMgr->m_CustomizeItem;
		for (int32 customizeRecordIndex = 0; customizeRecordIndex < customizeRecords.Num(); customizeRecordIndex++)
		{
			if (ItemInfo* customizeItemInfo = customizeRecords[customizeRecordIndex]->m_pItemInfo)
			{
				FName resultKey = FName(FString::Printf(TEXT("%d_%d_%d_%d"),
					static_cast<int32>(!customizeItemInfo->bIsWearing),
					static_cast<int32>(nItemType::GetEnum(customizeItemInfo->strItemType, false)),
					static_cast<int32>(nCustomType::GetEnum(customizeItemInfo->strCustomType, false)),
					customizeRecordIndex
				));
				
				m_CustomizeItemData.insert(std::make_pair(resultKey, customizeRecordIndex));
			}
		}
	}
}

void UMPWidget_ScrollCustomizeItem::SortCustomizeItemGridPanel()
{
	if (g_MPCustomizeMgrValid)
	{
		int32 columnMax = g_MPCustomizeMgr->m_ColumnMax;
		if (columnMax > 0)
		{
			int32 slotIndex = 0;
			for (auto& customizeItem: m_CustomizeItemData)
			{
				if (UMPWidgetSlot_CustomizeItem* pSlot = Cast<UMPWidgetSlot_CustomizeItem>(GridPanelCustomizeItem->GetChildAt(customizeItem.second)))
				{
					if (pSlot->GetVisibility() != ESlateVisibility::Collapsed)
					{
						if(UUniformGridSlot* pGridSlot = Cast<UUniformGridSlot>(pSlot->Slot))
						{
							pGridSlot->SetColumn(slotIndex % columnMax);
							pGridSlot->SetRow(slotIndex / columnMax);
							
							slotIndex++;
						}
					}
				}
			}
		}
	}
}