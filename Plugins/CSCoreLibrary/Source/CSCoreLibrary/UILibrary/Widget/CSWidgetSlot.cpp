// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidgetSlot.h"

#include "BaseWidget/CSImage.h"
#include "TableLibrary/DataTable/DataManager/MCStringTableDataRecordMgr.h"
#include "TableLibrary/Manager/CSTableMgr.h"
#include "UILibrary/Widget/WidgetInterface/CSWidgetInterface.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"

void UCSWidgetSlot::InitData()
{
	Super::InitData();

	this->UpdateVisibleBySelectState(m_bSelected);

	// FString _strText = m_strTextTitle.ToString();
	// FString _strText_Select = m_strTextTitleSelected.ToString();
	// FString _strChangeText = "";
	// FString _strChangeText_Select = "";
	// if(g_TableMgrValid)
	// {
	// 	if(g_TableMgr->GeteLocalType() == nLocalType::EN)
	// 	{
	// 		for(MCStringTableDetailRecord* pRecord:g_TableMgr->GetarrStringTableRecord())
	// 		{
	// 			if(pRecord->m_strKO == _strText && _strText != "")
	// 			{
	// 				_strChangeText = pRecord->m_strEN;
	// 				m_strTextTitle = TCHAR_TO_UTF8(*_strChangeText);
					this->SetButtonTextTitle(m_strTextTitle,false);
			// 		break;
			// 	}
			// }
			// for(MCStringTableDetailRecord* pRecord:g_TableMgr->GetarrStringTableRecord())
			// {
			// 	if(pRecord->m_strKO == _strText_Select && _strText != "")
			// 	{
			// 		_strChangeText_Select = pRecord->m_strEN;
			// 		m_strTextTitleSelected = TCHAR_TO_UTF8(*_strChangeText_Select);
					this->SetButtonTextTitle(m_strTextTitleSelected,true);
	// 				break;
	// 			}
	// 		}
	// 	}
	// }
	




}


void UCSWidgetSlot::ReleaseData()
{
	Super::ReleaseData();
}

void UCSWidgetSlot::LinkEvent()
{
	Super::LinkEvent();

	// 초기 클릭 이벤트 셋팅 : 슬롯의 부모 위젯으로 설정
	// 이벤트 위젯을 별도로 셋팅하고 싶다면 외부에서 SetClickEvent 함수를 호출해 다시 바인딩해주면 된다.
	if (m_pParentWidget.IsValid())
		this->SetClickEvent(m_pParentWidget.Get());
}

void UCSWidgetSlot::UnLinkEvent()
{
	this->RemoveClickEvent();

	Super::UnLinkEvent();
}

void UCSWidgetSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	this->SetSelected(m_bSelected);
	
	this->SetButtonTextTitle(m_strTextTitle);
	this->SetButtonTextTitle(m_strTextTitleSelected,true);
	
	if(SlotButton_Image_Icon)
		SlotButton_Image_Icon->SetBrush(m_Image);
	if(SlotButton_Image_Icon_Selected)
		SlotButton_Image_Icon_Selected->SetBrush(m_ImageSelected);
}

void UCSWidgetSlot::Show(ESlateVisibility visible /*= ESlateVisibility::SelfHitTestInvisible*/, float fDelayTime /*= 0.f*/, float fFadeTime /*= 0.f*/, float fDisplayTime /*= 0.f*/)
{
	Super::Show(visible, fDelayTime, fFadeTime, fDisplayTime);
}

void UCSWidgetSlot::Hide(float fDelatTime /*= 0.f*/, float fFadeTime /*= 0.f*/)
{
	Super::Hide(fDelatTime, fFadeTime);
}

void UCSWidgetSlot::SetClickEvent(UCSUserWidgetBase* _pEventParentWidget)
{
	this->RemoveClickEvent();

	if (_pEventParentWidget == nullptr)
		return;

	Super::SetEventParentWidget(_pEventParentWidget);

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UCSWidgetSlot::OnClicked);
		SlotButton->OnPressed.AddDynamic(this, &UCSWidgetSlot::OnPressed);
		SlotButton->OnReleased.AddDynamic(this, &UCSWidgetSlot::OnReleased);
		SlotButton->OnHovered.AddDynamic(this,&UCSWidgetSlot::OnHovered);
		SlotButton->OnUnhovered.AddDynamic(this,&UCSWidgetSlot::OnUnHovered);
	}

	if (SlotButton_Selected)
	{
		SlotButton_Selected->OnClicked.AddDynamic(this, &UCSWidgetSlot::OnClicked);
		SlotButton_Selected->OnPressed.AddDynamic(this, &UCSWidgetSlot::OnPressed);
		SlotButton_Selected->OnReleased.AddDynamic(this, &UCSWidgetSlot::OnReleased);
		SlotButton_Selected->OnHovered.AddDynamic(this,&UCSWidgetSlot::OnHovered);
		SlotButton_Selected->OnUnhovered.AddDynamic(this,&UCSWidgetSlot::OnUnHovered);
	}
}

void UCSWidgetSlot::RemoveClickEvent()
{
	if (SlotButton)
	{
		SlotButton->OnClicked.RemoveAll(this);
		SlotButton->OnPressed.RemoveAll(this);
		SlotButton->OnReleased.RemoveAll(this);
		SlotButton->OnHovered.RemoveAll(this);
		SlotButton->OnUnhovered.RemoveAll(this);
	}

	if (SlotButton_Selected)
	{
		SlotButton_Selected->OnClicked.RemoveAll(this);
		SlotButton_Selected->OnPressed.RemoveAll(this);
		SlotButton_Selected->OnReleased.RemoveAll(this);
		SlotButton_Selected->OnHovered.RemoveAll(this);
		SlotButton_Selected->OnUnhovered.RemoveAll(this);
	}
}

void UCSWidgetSlot::SetParentWidgetForWidgetTree()
{
	Super::SetParentWidgetForWidgetTree();

	m_eSlotParentType = ESlotParentTypeEnum::Parent_Normal;

	if (m_pParentWidget.IsValid())
	{
		//:: 부모위젯 클래스가 WidgetInterface 계열인 경우에는 위젯 인터페이스의 룰을 따르기 위해 타입을 지정한다.
		if (UCSWidgetInterface* _pWidgetInterface = ::Cast<UCSWidgetInterface>(m_pParentWidget.Get()))
			m_eSlotParentType = ESlotParentTypeEnum::Parent_WidgetInterface;
	}
}

void UCSWidgetSlot::SetParentWidgetInterfaceSlot(UCSUserWidgetBase* _pParentWidget)
{
	SetParentWidget(_pParentWidget);
	m_eSlotParentType = ESlotParentTypeEnum::Parent_WidgetInterface;
}

void UCSWidgetSlot::SetSelected(bool _bSelected)
{
	if (m_SlotIdx == INVALID_CLIENT_SLOT)
		return;

	m_bSelected = _bSelected;

	this->UpdateVisibleBySelectState(_bSelected);
}

void UCSWidgetSlot::SetEnabled(bool _bEnabled)
{
	if (m_SlotIdx == INVALID_CLIENT_SLOT)
		return;

	m_bEnabled = _bEnabled;

	this->SetIsEnabled(_bEnabled);
}

void UCSWidgetSlot::SetImageIcon(bool _bImageIcon)
{
	m_bImageIcon = _bImageIcon;
}

void UCSWidgetSlot::SetButtonEnabled(bool _bEnabled)
{
	if(SlotButton)
		SlotButton->SetIsEnabled(_bEnabled);
	if(SlotButton_Selected)
		SlotButton_Selected->SetIsEnabled(_bEnabled);
}

void UCSWidgetSlot::SetButtonTextTitle(FText text, bool bSelected)
{
	UCSTextBlock* pTextBlock = bSelected ? SlotButton_Text_Title_Selected :SlotButton_Text_Title;
	if (pTextBlock)
		pTextBlock->SetText(text);
}

void UCSWidgetSlot::SetButtonTextTitle(FName text, bool bSelected)
{
	SetButtonTextTitle(FText::FromName(text),bSelected);
}

void UCSWidgetSlot::UpdateVisibleBySelectState(bool _bSelected)
{
	if (SlotButton == nullptr || SlotButton_Selected == nullptr)
		return;

	if (_bSelected)
	{
		SlotButton->SetVisibility(ESlateVisibility::Collapsed);
		SlotButton_Selected->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SlotButton->SetVisibility(ESlateVisibility::Visible);
		SlotButton_Selected->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCSWidgetSlot::OnClicked()
{
	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemClicked(this);

	if (m_eSlotParentType == ESlotParentTypeEnum::Parent_Normal)
		this->SetSelected(!m_bSelected);
}

void UCSWidgetSlot::OnPressed()
{
	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemPressed(this);
}

void UCSWidgetSlot::OnReleased()
{
	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemReleased(this);
}

void UCSWidgetSlot::OnHovered()
{
	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemHovered(this);
}

void UCSWidgetSlot::OnUnHovered()
{
	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemUnHovered(this);
}
