// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidget_ViewPortPanel.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UILibrary/DataTable/DataManager/CSUIDataRecordMgr.h"
#include "UILibrary/DataTable/DataRecord/CSUIDataRecord.h"
#include "UILibrary/Widget/CSUIUtils.h"

void UCSWidget_ViewPortPanel::InitData()
{
	Super::InitData();
}

void UCSWidget_ViewPortPanel::ReleaseData()
{
	this->ClearPanels();

	Super::ReleaseData();
}

void UCSWidget_ViewPortPanel::CreatePanels(TArray<SPanelTypeInfo>& _PanelInfos, UWorld* _pWorld)
{
	int _nPanelSize = _PanelInfos.Num();
	for (int i = 0; i < _nPanelSize; ++i)
	{
		_PanelInfos[i].nUILayer = i;
		this->CreatePanel(_PanelInfos[i], _pWorld);
	}
}

void UCSWidget_ViewPortPanel::ClearPanels()
{
	for (int i = 0; i < nUIPanelType::Max; ++i)
		m_WidgetUIPanels[i] = nullptr;
}

UCSUserWidgetBase* UCSWidget_ViewPortPanel::CreatePanel(const SPanelTypeInfo& _PanelInfo, UWorld* _pWorld)
{
	const nUIPanelType::en ePanelType = _PanelInfo.ePanelType;

	if(ePanelType < 0 || ePanelType >= nUIPanelType::Max)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::CreatePanel - Panel Idx Error"));
		return nullptr;
	}

	if(m_WidgetUIPanels[ePanelType] != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::CreatePanel - Panel Already Exist"));
		return m_WidgetUIPanels[ePanelType];
	}

	FString _strPanelRecordKey = _PanelInfo.strUIRecordKey.ToString();
	UCSUserWidgetBase* _pWidgetPanel = nullptr;

	if (CSUIDataRecord* _pRecord = g_UIDataRecordMgr->FindRecord(_strPanelRecordKey))
	{
		_pWidgetPanel = CSUIUtils::LoadWidget<UCSUserWidgetBase>(_pRecord, _pWorld);
		if (_pWidgetPanel)
		{
			_pWidgetPanel->SetPanelType(ePanelType);
			_pWidgetPanel->SetParentWidgetForWidgetTree();

			_pWidgetPanel->AddToViewport(_PanelInfo.nUILayer);
			_pWidgetPanel->SetVisibility(ESlateVisibility::Collapsed);

			this->SetSlotLayOut(_pWidgetPanel);
			
			nBackBtnActionType::en eBackBtnActionType = nBackBtnActionType::GetEnum(_pRecord->_strBackBtnActionType.ToString(),false);
			_pWidgetPanel->SetBackBtnActionType(eBackBtnActionType);

			m_WidgetUIPanels[ePanelType] = _pWidgetPanel;

			UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::CreatePanel - Panel Create : %s"), *_strPanelRecordKey);
		}
	}
	return _pWidgetPanel;
}

void UCSWidget_ViewPortPanel::ShowUIPanel(const nUIPanelType::en& _eUIPanelType, ESlateVisibility _eVisible /*=ESlateVisibility::SelfHitTestInvisible*/)
{
	if (_eUIPanelType < 0 || _eUIPanelType >= nUIPanelType::Max)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::ShowUIPanel - Show Fail"));
		return;
	}

	if (m_WidgetUIPanels[_eUIPanelType] != nullptr)
		m_WidgetUIPanels[_eUIPanelType]->Show(_eVisible);
}

void UCSWidget_ViewPortPanel::HideUIPanel(const nUIPanelType::en& _eUIPanelType)
{
	if (_eUIPanelType < 0 || _eUIPanelType >= nUIPanelType::Max)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::HideUIPanel - Hide Fail"));
		return;
	}

	if (m_WidgetUIPanels[_eUIPanelType] != nullptr)
		m_WidgetUIPanels[_eUIPanelType]->Hide();
}

void UCSWidget_ViewPortPanel::HideAllUIPanel()
{
	for (int i = 0; i < static_cast<int>(nUIPanelType::Max); ++i)
	{
		if (m_WidgetUIPanels[i] != nullptr)
			m_WidgetUIPanels[i]->Hide();
	}
}

void UCSWidget_ViewPortPanel::ExeBackBtn(const nUIPanelType::en& _eUIPanelType)
{
	if (_eUIPanelType < 0 || _eUIPanelType >= nUIPanelType::Max)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::OnExeBackBtn - ExeBackBtn Fail"));
		return;
	}

	if (m_WidgetUIPanels[_eUIPanelType] != nullptr)
		m_WidgetUIPanels[_eUIPanelType]->OnExeBackBtn();
}

void UCSWidget_ViewPortPanel::SetSlotLayOut(UCSUserWidgetBase* _Widget)
{
	if (_Widget == nullptr)
		return;

	//:: Fill set
	if (UCanvasPanelSlot* _pSlot = ::Cast<UCanvasPanelSlot>(_Widget->Slot))
	{
		FAnchorData LayOutData;
		LayOutData.Anchors.Maximum.X = 1;
		LayOutData.Anchors.Maximum.Y = 1;

		LayOutData.Offsets.Top = 0;
		LayOutData.Offsets.Bottom = 0;
		LayOutData.Offsets.Right = 0;
		LayOutData.Offsets.Left = 0;

		_pSlot->SetLayout(LayOutData);
	}
}