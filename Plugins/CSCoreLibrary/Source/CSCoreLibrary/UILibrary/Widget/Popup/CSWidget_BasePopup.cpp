// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidget_BasePopup.h"


#include "Kismet/GameplayStatics.h"

#include "UILibrary/Manager/CSGameMsgMgr.h"
#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"

CSUIPopupShowValue::CSUIPopupShowValue()
{
	this->Init();
}

void CSUIPopupShowValue::Init()
{
	m_Handler.Unbind();
	m_eMsgType = nGameMsgType::Max;
	m_eShowButtonType = nPopupShowButtonType::Empty;
	m_strTitle = TEXT("");
	m_strMsgDesc = TEXT("");
	m_strIconName = TEXT("");
	m_strOKLocal = TEXT("");
	m_strCancelLocal = TEXT("");
	m_strPrizeBackGroundName = TEXT("");
	m_strBackGroundName = TEXT("");
}

void CSUIPopupShowValue::Init(CSPopupRecord* _pRecord)
{
	if(_pRecord)
	{
		m_Handler.Unbind();
		m_eMsgType = _pRecord->m_eMsgType;
		m_eShowButtonType = _pRecord->m_eShowButtonType;
		m_strTitle = _pRecord->m_strTitle;
		m_strMsgDesc = _pRecord->m_strMsgDesc;
		m_strIconName = _pRecord->m_strIconName;
		m_strOKLocal = _pRecord->m_strOKLocal;
		m_strCancelLocal = _pRecord->m_strCancelLocal;
		m_strPrizeBackGroundName = _pRecord->m_strPrizeBackGroundName;
		m_strBackGroundName = _pRecord->m_strBackgroundName;	
	}
}


void UCSWidget_BasePopup::InitData()
{
	Super::InitData();
}

void UCSWidget_BasePopup::ReleaseData()
{
	Super::ReleaseData();
}

void UCSWidget_BasePopup::LinkEvent()
{
	Super::LinkEvent();

	for(auto& itr: m_pButtons)
	{
		itr = nullptr;
	}
	BIND_BUTTON_EVENT(Button_Cancel,&UCSWidget_BasePopup::OnClickedCancel);
	BIND_BUTTON_EVENT(Button_OK,&UCSWidget_BasePopup::OnClickedOK);
	BIND_BUTTON_EVENT(Button_OKForSingle,&UCSWidget_BasePopup::OnClickedOK);
	
	if(Button_Cancel)
		m_pButtons[nButton::Cancel] = Button_Cancel;
	if(Button_OK)	
		m_pButtons[nButton::Ok] = Button_OK;
	if(Button_OKForSingle)
		m_pButtons[nButton::OkForSingle] = Button_OKForSingle;
}

void UCSWidget_BasePopup::UnLinkEvent()
{
	UNBIND_BUTTON_EVENT_ALL(Button_Cancel);
	UNBIND_BUTTON_EVENT_ALL(Button_OK);
	UNBIND_BUTTON_EVENT_ALL(Button_OKForSingle);

	Super::UnLinkEvent();
}

void UCSWidget_BasePopup::Show(ESlateVisibility visible, float fDelayTime, float fFadeTime, float fDisplayTime)
{
	FString strOKLocal = CSDefineRecordMgr::GetValue_String(m_PopupValue.m_strOKLocal);
	FText textOKLocal = FText::FromString(strOKLocal.IsEmpty() ? m_PopupValue.m_strOKLocal : strOKLocal);
	if(m_PopupValue.m_eShowButtonType == nPopupShowButtonType::Ok)
	{
		
		if(Text_OkForSingle)
			Text_OkForSingle->SetText(textOKLocal);
	}
	else if (m_PopupValue.m_eShowButtonType == nPopupShowButtonType::OkCancel)
	{
		if(Text_OK)
			Text_OK->SetText(textOKLocal);
		
		FString strCancelLocal = CSDefineRecordMgr::GetValue_String(m_PopupValue.m_strCancelLocal);
		FText textCancelLocal = FText::FromString(strCancelLocal.IsEmpty() ? m_PopupValue.m_strCancelLocal : strCancelLocal);
		if(Text_Cancel)
			Text_Cancel->SetText(textCancelLocal);
	}
	
	this->ShowButtons(m_PopupValue.m_eShowButtonType);
	Super::Show(visible, fDelayTime, fFadeTime, fDisplayTime);
	
}

void UCSWidget_BasePopup::Hide(float fDelatTime, float fFadeTime)
{
	Super::Hide(fDelatTime, fFadeTime);
}

void UCSWidget_BasePopup::OnClickedCancel()
{
	OnClickedCancelEvent();
}

void UCSWidget_BasePopup::OnClickedOK()
{
	OnClickedOKEvent();
}

void UCSWidget_BasePopup::ShowButtons(nPopupShowButtonType::en eButtonType)
{
	this->AllDisableButton();
	
	switch(eButtonType)
	{
	case nPopupShowButtonType::Ok:
		{
			if (Button_OKForSingle != nullptr)
			{
				Button_OKForSingle->SetVisibility(ESlateVisibility::Visible);
			}
		}
		break;
	case nPopupShowButtonType::OkCancel:
		{
			if (Button_OK != nullptr)
			{
				Button_OK->SetVisibility(ESlateVisibility::Visible);
			}

			if (Button_Cancel != nullptr)
			{
				Button_Cancel->SetVisibility(ESlateVisibility::Visible);
			}
		}
		break;
	}
}

void UCSWidget_BasePopup::AllDisableButton()
{
	for(auto& itr: m_pButtons)
	{
		if(itr)
			itr->SetVisibility(ESlateVisibility::Collapsed);
	}	
}

void UCSWidget_BasePopup::OnClickedOKEvent()
{
	m_PopupValue.m_Handler.ExecuteIfBound(EPopupEventID::Ok);


	RemoveFromParent();			
}	

void UCSWidget_BasePopup::OnClickedCancelEvent()
{
	m_PopupValue.m_Handler.ExecuteIfBound(EPopupEventID::Cancel);
	
	RemoveFromParent();
}
