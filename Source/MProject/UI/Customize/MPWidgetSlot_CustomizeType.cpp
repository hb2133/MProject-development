// Fill out your copyright notice in the Description page of Project Settings.


#include "MPWidgetSlot_CustomizeType.h"
#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"

#include "UILibrary/Widget/BaseWidget/CSImage.h"

void UMPWidgetSlot_CustomizeType::InitData()
{
	Super::InitData();

	m_strCustomizeType = nullptr;
}

void UMPWidgetSlot_CustomizeType::ReleaseData()
{
	Super::ReleaseData();
}

void UMPWidgetSlot_CustomizeType::LinkEvent()
{
	Super::LinkEvent();
}

void UMPWidgetSlot_CustomizeType::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMPWidgetSlot_CustomizeType::SetCustomizeType(const FString& customizeType)
{
	m_strCustomizeType = customizeType;

	if (g_MPCustomizeSpriteRecordMgr)
	{
		FString strSpriteTid = "Btn_Type_";
		if (customizeType == "Chest" || customizeType == "Pants")
		{
			strSpriteTid += "Dress";
		}
		else
		{
			strSpriteTid += customizeType;
		}
		
		FString strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
		SlotButton_Image_Icon->SetBrushFromSpriteName(strSpriteName);

		strSpriteTid += "_Selected";
		strSpriteName = g_MPCustomizeSpriteRecordMgr->GetSpriteName(strSpriteTid);
		SlotButton_Image_Icon_Selected->SetBrushFromSpriteName(strSpriteName);
	}
}
