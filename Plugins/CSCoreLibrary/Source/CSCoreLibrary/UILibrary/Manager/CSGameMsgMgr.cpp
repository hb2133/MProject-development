// Fill out your copyright notice in the Description page of Project Settings.


#include "CSGameMsgMgr.h"


#include "..\DataTable\DataManager\CSPopupRecordMgr.h"
#include "UILibrary/Widget/Popup/CSWidget_BasePopup.h"
#include "UILibrary/Widget/CSUIUtils.h"

void UCSGameMsgMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSGameMsgMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UCSGameMsgMgr::Release()
{

}

void UCSGameMsgMgr::Load()
{

}

void UCSGameMsgMgr::Tick(float _dt)
{
	Super::Tick(_dt);
}

UCSUserWidgetBase* UCSGameMsgMgr::CreateMessageWidget(nGameMsgType::en eMassageType)
{
	FString strBlueprint = TEXT("");
	switch (eMassageType)
	{
	case nGameMsgType::MsgPopup:
		strBlueprint = TEXT("W_QuizResult_BP");
		break;
	case nGameMsgType::DoubleMsgPopup:
		strBlueprint = TEXT("W_DoubleMesaagePopup_BP");
		break;
	case nGameMsgType::ResultMsgPopup:
		strBlueprint = TEXT("W_ResultMessagePopup_BP");
		break;
	case nGameMsgType::GoogleMsgPopup:
		strBlueprint = TEXT("W_GoogleLoginMessagePopup_BP");
	case nGameMsgType::GoogleResultMsgPopup:
		strBlueprint = TEXT("W_GoogleLoginMessagePopup_BP");
		break;
	}

	TWeakObjectPtr<UCSUserWidgetBase> pFindWidget = nullptr;
	if(TWeakObjectPtr<UCSUserWidgetBase>* pWidget = m_mapMessageWidget.Find(eMassageType))
	{
		if(pWidget->IsValid() == false)
		{
			*pWidget = CSUIUtils::LoadWidget(FName(*strBlueprint),GetWorld());
		}
		pFindWidget = *pWidget;		
	}
	else
	{
		if(UCSUserWidgetBase* pWidgetBase = CSUIUtils::LoadWidget(FName(*strBlueprint),GetWorld()))
		{
			pFindWidget = m_mapMessageWidget.Add(eMassageType,pWidgetBase);
		}
	}

	if ((pFindWidget.IsValid() == false)) { return nullptr; }
	
	return pFindWidget.Get();
}

void UCSGameMsgMgr::ShowMessageBox(const CSUIPopupShowValue& popupValue, float delayTime, bool bHighLayerBox)
{
	MsgDataPackPtr newMsgPack = MakeShareable(new MsgDataPack());
	
	newMsgPack->eMsgType = popupValue.m_eMsgType;
	newMsgPack->eMsgLayerType = (bHighLayerBox) ? nMsgLayerType::High:nMsgLayerType::Normal;
	newMsgPack->m_PopupValue = popupValue;
	this->ShowMessageWidget(newMsgPack);
}

//_BindObject : 바인딩 할 함수가 있는 오브젝트(클래스)
//_FuncName : 바인딩 할 함수. UFUNCTION() 이어야 하고 _BindObject의 클래스 내부에 있는 함수여야 함 
bool UCSGameMsgMgr::ShowMessageBox(const FString& _popupTid, UObject* _BindObject, FString _FuncName)
{
	CSUIPopupShowValue popupValue;
	if (CSPopupRecord* _pRecord = g_PopupRecordMgr->FindRecord(_popupTid))
	{		
		popupValue.Init(_pRecord);
		if(_BindObject)
		{
			if(_BindObject->FindFunction(FName(*_FuncName)))
				popupValue.m_Handler.BindUFunction(_BindObject,FName(*_FuncName));
			else
				UE_LOG(LogTemp,Warning,TEXT("FuncName : %s Not Found In Class %s."),*_FuncName,*_BindObject->GetClass()->GetName());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("BindObject Is Null."));
		}
		
		
		ShowMessageBox(popupValue);
		return true;
	}
	return false;
}

void UCSGameMsgMgr::ShowMessageWidget(const MsgDataPackPtr messagePack)
{
	if(UCSUserWidgetBase* pWidget = CreateMessageWidget(messagePack->eMsgType) )
	{
		switch (messagePack->eMsgType)
		{
		case nGameMsgType::MsgPopup:
			{
				if(UCSWidget_BasePopup* pMessagePopup = ::Cast<UCSWidget_BasePopup>(pWidget) )
				{
					pMessagePopup->m_PopupValue = messagePack->m_PopupValue;
					pMessagePopup->AddToViewport(messagePack->eMsgLayerType);
					pMessagePopup->Show(ESlateVisibility::Visible);
				}
			}
			break;
		case nGameMsgType::DoubleMsgPopup:
			{
				if(UCSWidget_BasePopup* pMessagePopup = ::Cast<UCSWidget_BasePopup>(pWidget) )
				{
					pMessagePopup->m_PopupValue = messagePack->m_PopupValue;
					pMessagePopup->AddToViewport(messagePack->eMsgLayerType);
					pMessagePopup->Show(ESlateVisibility::Visible);
				}
			}break;
		case nGameMsgType::ResultMsgPopup:
			{
				if(UCSWidget_BasePopup* pMessagePopup = ::Cast<UCSWidget_BasePopup>(pWidget) )
				{
					pMessagePopup->m_PopupValue = messagePack->m_PopupValue;

					pMessagePopup->AddToViewport(messagePack->eMsgLayerType);
					pMessagePopup->Show(ESlateVisibility::Visible);
				}
			}break;
		case nGameMsgType::GoogleMsgPopup:
			{
				if(UCSWidget_BasePopup* pMessagePopup = ::Cast<UCSWidget_BasePopup>(pWidget) )
				{
					pMessagePopup->m_PopupValue = messagePack->m_PopupValue;
					pMessagePopup->AddToViewport(messagePack->eMsgLayerType);
					pMessagePopup->Show(ESlateVisibility::Visible);
				}
			}break;

		case nGameMsgType::GoogleResultMsgPopup:
			{
				if(UCSWidget_BasePopup* pMessagePopup = ::Cast<UCSWidget_BasePopup>(pWidget) )
				{
					pMessagePopup->m_PopupValue = messagePack->m_PopupValue;
					pMessagePopup->AddToViewport(messagePack->eMsgLayerType);
					pMessagePopup->Show(ESlateVisibility::Visible);
				}
			}break;
			default:
				break;
		}
	}	
}
