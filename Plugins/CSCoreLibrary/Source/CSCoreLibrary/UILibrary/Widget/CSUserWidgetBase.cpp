// Fill out your copyright notice in the Description page of Project Settings.


#include "CSUserWidgetBase.h"
#include "Animation/WidgetAnimation.h"
#include "UILibrary/Manager/CSUIMgr.h"
#include "Blueprint/WidgetTree.h"

void UCSUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	this->InitData();
	this->LinkEvent();

	this->InitWidgetBaseAni();
}

void UCSUserWidgetBase::NativeDestruct()
{
	this->ReleaseData();
	this->UnLinkEvent();

	this->ReleaseWidgetBaseAni();

	Super::NativeDestruct();
}

void UCSUserWidgetBase::LinkEvent()
{
	UnLinkEvent();
}

void UCSUserWidgetBase::InitData()
{

}

void UCSUserWidgetBase::Show(ESlateVisibility visible /*=ESlateVisibility::SelfHitTestInvisible*/, float fDelayTime /*=0.f*/, float fFadeTime /*=0.f*/, float fDisplayTime /*=0.f*/)
{
	this->SetVisibility(visible);

	if(ShowUIAni) 
		this->PlayAnimation(ShowUIAni);
	
	if(g_UIMgrValid) 
		g_UIMgr->AddBackBtnType(this->GetPanelType());
}

void UCSUserWidgetBase::Hide(float fDelatTime /*=0.f*/, float fFadeTime /*=0.f*/)
{
	if (HideUIAni)
	{
		this->PlayAnimation(HideUIAni);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
		
		if(g_UIMgrValid) 
			g_UIMgr->RemoveBackBtnType(this->GetPanelType());
	}
}

void UCSUserWidgetBase::ShowAndPopup()
{
	Show();
	g_UIMgr->m_arrStackWidget.Add(this);
}

void UCSUserWidgetBase::InitWidgetBaseAni()
{
	if (ShowUIAni)
	{
		ShowAniFinishDelegate.BindDynamic(this, &UCSUserWidgetBase::OnFinishShowAni);
		this->BindToAnimationFinished(ShowUIAni, ShowAniFinishDelegate);
	}

	if (HideUIAni)
	{
		HideAniFinishDelegate.BindDynamic(this, &UCSUserWidgetBase::OnFinishHideAni);
		this->BindToAnimationFinished(HideUIAni, HideAniFinishDelegate);
	}
}

void UCSUserWidgetBase::ReleaseWidgetBaseAni()
{
	if (ShowUIAni) 
		this->UnbindAllFromAnimationFinished(ShowUIAni);
	
	if (HideUIAni) 
		this->UnbindAllFromAnimationFinished(HideUIAni);
}

void UCSUserWidgetBase::ExeBackBtnAction()
{
	switch (this->GetBackBtnActionType())
	{
		case nBackBtnActionType::NoAction:
		{
		}
		break;
		case nBackBtnActionType::OnClose:
		{
			OnClosePopup();
		}
		break;
	case nBackBtnActionType::OnClosePopup:
		{
			
		}break;
	}
}

bool UCSUserWidgetBase::OnExtBackButton()
{
	UE_LOG(LogTemp,Warning,TEXT("OnClicked BackBtn"))
	this->Hide();
	return true;
}

void UCSUserWidgetBase::OnClosePopup()
{

	if(m_pParentWidget.IsValid())
	{
		UE_LOG(LogTemp,Warning,TEXT("Parent Close Popup %s"),*m_pParentWidget->GetName());
		m_pParentWidget->OnParentClosePopup();
	}
}

bool UCSUserWidgetBase::IsActive()
{
	if(GetVisibility() == ESlateVisibility::Hidden || GetVisibility() == ESlateVisibility::Collapsed)
		return false;
	return true;
}

void UCSUserWidgetBase::SetPanelType(const nUIPanelType::en& _ePanelTpye)
{
	m_ePanelType = _ePanelTpye;
}

void UCSUserWidgetBase::SetBackBtnActionType(const nBackBtnActionType::en& _eBackBtnActionTpye)
{
	m_eBackBtnActionType = _eBackBtnActionTpye;
}

void UCSUserWidgetBase::SetParentWidgetForWidgetTree()
{
	if (WidgetTree != nullptr)
	{
		WidgetTree->ForEachWidget([this](UWidget* Widget)
		{
			if (UCSUserWidgetBase* _pWidgetBase = ::Cast<UCSUserWidgetBase>(Widget))
			{
				_pWidgetBase->SetParentWidget(this);
				_pWidgetBase->SetParentWidgetForWidgetTree();
			}
		});
	}
}

UCSUserWidgetBase* UCSUserWidgetBase::SearchEventParentWidget()
{
	UCSUserWidgetBase* _pWidgetBase = m_pEventParentWidget.Get();

	if (_pWidgetBase == nullptr)
		_pWidgetBase = m_pParentWidget.Get();

	return _pWidgetBase;
}

void UCSUserWidgetBase::OnFinishShowAni()
{
	//:: Finish Show UI Ani
}
void UCSUserWidgetBase::OnFinishHideAni()
{
	//:: Finish Hide UI Ani
	this->SetVisibility(ESlateVisibility::Collapsed);
	
	if (g_UIMgrValid) 
		g_UIMgr->RemoveBackBtnType(this->GetPanelType());
}
