// Fill out your copyright notice in the Description page of Project Settings.


#include "CSUIMgr.h"

#include "Engine/World.h"
#include "Engine/BlueprintGeneratedClass.h"

#include "UILibrary/DataTable/DataManager/CSUIDataRecordMgr.h"
#include "UILibrary/DataTable/DataRecord/CSUIDataRecord.h"
#include "Engine/AssetManager.h"

#include "UILibrary/Widget/CSUIUtils.h"
#include "UILibrary/Widget/CSWidgetPanel.h"


/////////////////////////////////
// CSUIBackBtnTypes

CSUIBackBtnTypes::CSUIBackBtnTypes()
{
}

CSUIBackBtnTypes::~CSUIBackBtnTypes()
{
}

void CSUIBackBtnTypes::Add(UCSUserWidgetBase* _pWidgetPanel)
{
	nUIPanelType::en _ePanelType = _pWidgetPanel->GetPanelType();
	Add(_ePanelType);
}

void CSUIBackBtnTypes::Add(const nUIPanelType::en& _ePanelType)
{
	if (IsExist(_ePanelType))
		return;

	m_arrPanelTypes.Add(_ePanelType);
	m_arrPanelTypes.Sort();
}

bool CSUIBackBtnTypes::IsExist(UCSUserWidgetBase* _pWidgetPanel)
{
	if (_pWidgetPanel)
		return IsExist(_pWidgetPanel->GetPanelType());
	return false;
}
bool CSUIBackBtnTypes::IsExist(const nUIPanelType::en& _ePanelType)
{
	return (m_arrPanelTypes.Find(_ePanelType) != INDEX_NONE);
}

nUIPanelType::en CSUIBackBtnTypes::PopLastIndex()
{
	if (m_arrPanelTypes.Num() <= 0)
		return nUIPanelType::Max;

	nUIPanelType::en _eLastPanelType = m_arrPanelTypes.Pop();
	return _eLastPanelType;
}

nUIPanelType::en CSUIBackBtnTypes::GetLastIndex(const int& nPrevIdx /*= 0*/)
{
	if (m_arrPanelTypes.Num() <= 0)
		return nUIPanelType::Max;

	nUIPanelType::en _eLastPanelType = m_arrPanelTypes.Last(nPrevIdx);
	return _eLastPanelType;
}

void CSUIBackBtnTypes::Remove(UCSUserWidgetBase* _pWidgetPanel)
{
	if (m_arrPanelTypes.Num() <= 0)
		return;

	nUIPanelType::en _ePanelType = _pWidgetPanel->GetPanelType();
	m_arrPanelTypes.Remove(_ePanelType);
}

void CSUIBackBtnTypes::Remove(nUIPanelType::en _ePanelType)
{
	m_arrPanelTypes.Remove(_ePanelType);
}

void CSUIBackBtnTypes::RemoveAll()
{
	m_arrPanelTypes.Reset();
}

int CSUIBackBtnTypes::GetArrayIndex(nUIPanelType::en _ePanelType)
{
	int findIndex = m_arrPanelTypes.Find(_ePanelType);

	if (findIndex == INDEX_NONE)
		return INDEX_NONE;

	return findIndex;
}

/////////////////////////////////
// UCSUIMgr

void UCSUIMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSUIMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UCSUIMgr::Release()
{
	this->ClearPanels();
}

void UCSUIMgr::Load()
{
}

void UCSUIMgr::CreatePanels(TArray<SPanelTypeInfo>& _Infos, UWorld* _pWorld)
{
	if (CSUIDataRecord* _pRecord = g_UIDataRecordMgr->FindRecord(FString("ViewPort")))
	{
		if (UCSWidget_ViewPortPanel* _pWidgetViewPort = CSUIUtils::LoadWidget<UCSWidget_ViewPortPanel>(_pRecord, _pWorld))
		{
			_pWidgetViewPort->AddToViewport();
			_pWidgetViewPort->CreatePanels(_Infos, _pWorld);

			m_WidgetViewPort = _pWidgetViewPort;
		}
	}
}

void UCSUIMgr::ClearPanels()
{
	if (UCSWidget_ViewPortPanel* _pViewPortPanel = m_WidgetViewPort.Get())
		CSUIUtils::DestroyWidget(_pViewPortPanel);

	m_WidgetViewPort = nullptr;
	m_BackBtnTypes.RemoveAll();
}

void UCSUIMgr::ShowUIPanel(const nUIPanelType::en& _eUIPanelType, ESlateVisibility _eVisible /*= ESlateVisibility::SelfHitTestInvisible*/)
{
	if (UCSWidget_ViewPortPanel* _pViewPortPanel = m_WidgetViewPort.Get())
		_pViewPortPanel->ShowUIPanel(_eUIPanelType);
}

void UCSUIMgr::HideUIPanel(const nUIPanelType::en& _eUIPanelType)
{
	if (UCSWidget_ViewPortPanel* _pViewPortPanel = m_WidgetViewPort.Get())
		_pViewPortPanel->HideUIPanel(_eUIPanelType);
}

void UCSUIMgr::HideAllUIPanel()
{
	if (UCSWidget_ViewPortPanel* _pViewPortPanel = m_WidgetViewPort.Get())
		_pViewPortPanel->HideAllUIPanel();
}

void UCSUIMgr::ToggleUIPanel(const nUIPanelType::en& _eUIPanelType)
{
	if (UCSWidget_ViewPortPanel* _pViewPortPanel = m_WidgetViewPort.Get())
	{
		// if(UCSWidgetPanel* pPanel = ::Cast<UCSWidgetPanel>(GetUIPanel(_eUIPanelType)))
		// {
		// 	if(pPanel->IsActive())
		// 		pPanel->Hide();
		// 	else
		// 		pPanel->Show();
		// }
	}
}

void UCSUIMgr::OnExeBackBtn(int nPrevIdx /*= 0*/)
{
	if (m_BackBtnTypes.GetPanelTypeCount() <= 0)
	{
		//:: not exist back btn action Panel
	}
	else
	{
		if (UCSWidget_ViewPortPanel* _pViewPortPanel = m_WidgetViewPort.Get())
		{
			nUIPanelType::en _eLastPanelIndex = m_BackBtnTypes.GetLastIndex();
			_pViewPortPanel->ExeBackBtn(_eLastPanelIndex);
		}
	}
}

void UCSUIMgr::OnExtBackButton()
{
	if(!m_arrStackWidget.IsEmpty())
	{
		int32 LastIndex = m_arrStackWidget.Num() - 1;

		if(m_arrStackWidget.IsValidIndex(LastIndex))
		{
			if(m_arrStackWidget[LastIndex]->OnExtBackButton())
			{
				m_arrStackWidget.RemoveAt(LastIndex);
			}
		}
	}
}


void UCSUIMgr::AddBackBtnType(const nUIPanelType::en& _eUIPanelType)
{
	if(_eUIPanelType != nUIPanelType::Max)
		m_BackBtnTypes.Add(_eUIPanelType);
}

void UCSUIMgr::RemoveBackBtnType(const nUIPanelType::en& _eUIPanelType)
{
	if(_eUIPanelType != nUIPanelType::Max)
		m_BackBtnTypes.Remove(_eUIPanelType);
}