// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "UILibrary/Define/CSDefine_UICommon.h"
#include "CSWidget_ViewPortPanel.generated.h"

class UCSCanvasPanel;

UCLASS()
class CSCORELIBRARY_API UCSWidget_ViewPortPanel : public UCSUserWidgetBase
{
	GENERATED_BODY()
	
private:
	FString _OnCloseKey = FString("OnClose");
	FString _NoActionKey = FString("NoAction");

	UPROPERTY()
	UCSUserWidgetBase* m_WidgetUIPanels[nUIPanelType::Max];

public:
	virtual void InitData() override;
	virtual void ReleaseData() override;

public:
	void CreatePanels(TArray<SPanelTypeInfo>& _PanelInfos, UWorld* _pWorld);
	UCSUserWidgetBase* CreatePanel(const SPanelTypeInfo& _PanelInfo, UWorld* _pWorld);
	void ClearPanels();

	void ShowUIPanel(const nUIPanelType::en& _eUIPanelType, ESlateVisibility _eVisible = ESlateVisibility::SelfHitTestInvisible);
	void HideUIPanel(const nUIPanelType::en& _eUIPanelType);
	void HideAllUIPanel();

	template <typename T = UCSUserWidgetBase>
	T* GetUIPanel(const nUIPanelType::en& _eUIPanelType)
	{
		if (_eUIPanelType < 0 || _eUIPanelType >= nUIPanelType::Max)
		{
			UE_LOG(LogTemp, Warning, TEXT("UCSWidget_ViewPortPanel::GetUIPanel - Get UI Panel Fail"));
			return nullptr;
		}

		if (m_WidgetUIPanels[_eUIPanelType] != nullptr)
			return ::Cast<T>(m_WidgetUIPanels[_eUIPanelType]);

		return nullptr;
	}

public:
	void ExeBackBtn(const nUIPanelType::en& _eUIPanelType);

private:
	void SetSlotLayOut(UCSUserWidgetBase* _Widget);
};
