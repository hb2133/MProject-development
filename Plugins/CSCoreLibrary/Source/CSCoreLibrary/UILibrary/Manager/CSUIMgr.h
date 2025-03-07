// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "UILibrary/Define/CSDefine_UICommon.h"
#include "UILibrary/Widget/CSWidgetPanel.h"
#include "UILibrary/Widget/ViewPort/CSWidget_ViewPortPanel.h"
#include "CSUIMgr.generated.h"

class UWorld;
class UCSUserWidgetBase;

class CSUIBackBtnTypes
{
public:
	CSUIBackBtnTypes();
	virtual ~CSUIBackBtnTypes();

public:
	void Add(UCSUserWidgetBase* _pWidgetPanel);
	void Add(const nUIPanelType::en& _ePanelType);
	bool IsExist(UCSUserWidgetBase* _pWidgetPanel);
	bool IsExist(const nUIPanelType::en& _ePanelType);

	nUIPanelType::en PopLastIndex();
	nUIPanelType::en GetLastIndex(const int& nPrevIdx = 0);

	void Remove(UCSUserWidgetBase* _pWidgetPanel);
	void Remove(nUIPanelType::en _ePanelType);
	void RemoveAll();

	int GetArrayIndex(nUIPanelType::en _ePanelType);
	int GetPanelTypeCount() { return m_arrPanelTypes.Num(); }
	TArray<nUIPanelType::en>& GetPanelTypes() { return m_arrPanelTypes; }

private:
	TArray<nUIPanelType::en> m_arrPanelTypes;
};

UCLASS()
class CSCORELIBRARY_API UCSUIMgr : public UCSBaseManager
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void Release() override;
	void Load() override;
 
public:
	void CreatePanels(TArray<SPanelTypeInfo>& _Infos, UWorld* _pWorld);
	void ClearPanels();

	void ShowUIPanel(const nUIPanelType::en& _eUIPanelType, ESlateVisibility _eVisible = ESlateVisibility::SelfHitTestInvisible);
	void HideUIPanel(const nUIPanelType::en& _eUIPanelType);
	void HideAllUIPanel();
	void ToggleUIPanel(const nUIPanelType::en& _eUIPanelType);

	template <typename T = UCSUserWidgetBase>
	T* GetUIPanel()
	{
		if (UCSWidgetPanel* _pViewPortPanel = m_pMainMobileWidget.Get())
			return _pViewPortPanel;
		return nullptr;
	}
	
public:
	void OnExeBackBtn(int nPrevIdx = 0);
	void OnExtBackButton();
	void AddBackBtnType(const nUIPanelType::en& _eUIPanelType);
	void RemoveBackBtnType(const nUIPanelType::en& _eUIPanelType);

public:
	UPROPERTY()
	TWeakObjectPtr<UCSWidget_ViewPortPanel> m_WidgetViewPort;	

	UPROPERTY()
	TWeakObjectPtr<UCSWidgetPanel> m_pMainMobileWidget;
	CSUIBackBtnTypes m_BackBtnTypes;

	
	
	TArray<UCSUserWidgetBase*> m_arrStackWidget;
};

#define g_UIMgrValid ( UCSGameGlobal::Get().IsValidManager<UCSUIMgr>() )
#define g_UIMgr ( UCSGameGlobal::Get().GetManager<UCSUIMgr>() )
