// Fill out your copyright notice in the Description page of Project Settings.

#include "MProjectWidget_CustomizeItem.h"
#include "MPWidgetSlot_CustomizeItem.h"
#include "MPWidgetSlot_CustomizeType.h"
#include "MPWidget_ScrollCustomizeItem.h"
#include "MPWidget_ScrollCustomizeType.h"
#include "Components/UniformGridSlot.h"
#include "MProject/Define/MPCustomizeCommon.h"

#include "CoreLibrary/Manager/CSFileManager.h"
#include "MProject/Manager/MPCustomizeMgr.h"
#include "UILibrary/Widget/BaseWidget/CSUniformGridPanel.h"


void UMProjectWidget_CustomizeItem::InitData()
{
	Super::InitData();

	initScrollCustomizeType();
	if (ScrollCustomizeType)
	{
		ScrollCustomizeType->SetParentWidget(this);
	}
	if (ScrollCustomizeItem)
	{
		ScrollCustomizeItem->SetParentWidget(this);
	}
}

void UMProjectWidget_CustomizeItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidget_CustomizeItem::LinkEvent()
{
	Super::LinkEvent();
}

void UMProjectWidget_CustomizeItem::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMProjectWidget_CustomizeItem::OnChildItemClicked(UCSUserWidgetBase* _pChildWidget)
{
	Super::OnChildItemClicked(_pChildWidget);

	GetParentWidget()->OnChildItemClicked(_pChildWidget);
	
	if (UMPWidgetSlot_CustomizeType* pSlot = Cast<UMPWidgetSlot_CustomizeType>(_pChildWidget))
	{
		if (ScrollCustomizeType)
		{
			ScrollCustomizeType->AddSelectedChild(pSlot);
		}
		
		if (ScrollCustomizeItem)
		{
			if (UCSUniformGridPanel* pGridPanelCustomizeItem = ScrollCustomizeItem->GridPanelCustomizeItem)
			{
				if (pSlot->GetCustomizeType() == "All")
				{
					for (int32 customizeItemIndex = 0; customizeItemIndex < pGridPanelCustomizeItem->GetChildrenCount(); customizeItemIndex++)
					{
						UMPWidgetSlot_CustomizeItem* pItem = Cast<UMPWidgetSlot_CustomizeItem>(pGridPanelCustomizeItem->GetChildAt(customizeItemIndex));
						pItem->Show();
					}
				}
				else
				{
					for (int32 customizeItemIndex = 0; customizeItemIndex < pGridPanelCustomizeItem->GetChildrenCount(); customizeItemIndex++)
					{
						UMPWidgetSlot_CustomizeItem* pItem = Cast<UMPWidgetSlot_CustomizeItem>(pGridPanelCustomizeItem->GetChildAt(customizeItemIndex));
						if (pItem->GetSlotItemInfo()->strCustomType == pSlot->GetCustomizeType())
						{
							pItem->Show();
						}
						else
						{
							pItem->Hide();
						}
					}
				}

				ScrollCustomizeItem->SortCustomizeItemGridPanel();
			}
		}
	}
}

void UMProjectWidget_CustomizeItem::initScrollCustomizeType()
{
	TArray<FString> customizeTypes = {"All", "Bag", "Chest", "Pants", "Tool"};
	
	if (ScrollCustomizeType)
	{
		if(UClass* slotClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass,"S_CustomizeType_BP"))
		{
			for (FString strcustomizeType : customizeTypes)
			{
				if(UMPWidgetSlot_CustomizeType* pSlot = CreateWidget<UMPWidgetSlot_CustomizeType>(this, slotClass))
				{
					ScrollCustomizeType->AddScrollChild(pSlot, this);
					if (strcustomizeType == customizeTypes[0])
					{
						ScrollCustomizeType->AddSelectedChild(pSlot);
					}
					
					pSlot->SetCustomizeType(strcustomizeType);
					pSlot->SetClickEvent(this);
				}
			}
		}
	}
}
