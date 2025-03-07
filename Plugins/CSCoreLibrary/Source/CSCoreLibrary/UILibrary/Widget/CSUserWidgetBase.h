// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoreLibrary/Define/CSClientDefine.h"
#include "UILibrary/Define/CSDefine_UICommon.h"

#include "CSUserWidgetBase.generated.h"

class UWidgetAnimation;

UCLASS()
class CSCORELIBRARY_API UCSUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	FWidgetAnimationDynamicEvent ShowAniFinishDelegate;
	FWidgetAnimationDynamicEvent HideAniFinishDelegate;

	UPROPERTY(BlueprintReadWrite, Category = "CSWidget")
	UWidgetAnimation* ShowUIAni;

	UPROPERTY(BlueprintReadWrite, Category = "CSWidget")
	UWidgetAnimation* HideUIAni;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	virtual void Show(ESlateVisibility visible = ESlateVisibility::SelfHitTestInvisible, float fDelayTime = 0.f, float fFadeTime = 0.f, float fDisplayTime = 0.f);
	virtual void Hide(float fDelatTime = 0.f, float fFadeTime = 0.f);

	virtual void InitData();
	virtual void ReleaseData() {}
	virtual void LinkEvent();
	virtual void UnLinkEvent() {}

	virtual void OnExeBackBtn() { this->ExeBackBtnAction(); }
	virtual bool OnExtBackButton();
	virtual void OnClosePopup();
	virtual void OnParentClosePopup() {}

	virtual bool IsActive();
public:
	void SetPanelType(const nUIPanelType::en& _ePanelTpye);
	void SetBackBtnActionType(const nBackBtnActionType::en& _eBackBtnActionTpye);
	void SetParentWidget(UCSUserWidgetBase* _pWidget) { m_pParentWidget = _pWidget; }
	void SetEventParentWidget(UCSUserWidgetBase* _pWidget) { m_pEventParentWidget = _pWidget; }

	nUIPanelType::en GetPanelType() { return m_ePanelType; }
	nBackBtnActionType::en GetBackBtnActionType() { return m_eBackBtnActionType; }
	UCSUserWidgetBase* GetParentWidget() { return m_pParentWidget.Get(); }
	UCSUserWidgetBase* GetEventParentWidget() { return m_pEventParentWidget.Get(); }


	void ShowAndPopup();


public:
	void InitWidgetBaseAni();
	void ReleaseWidgetBaseAni();

	void ExeBackBtnAction();
	
	virtual void SetClickEvent(UCSUserWidgetBase* _pEventParentWidget) {}
	virtual void RemoveClickEvent() {}
	
	virtual void SetParentWidgetForWidgetTree();
	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) {}
	virtual void OnChildItemPressed(UCSUserWidgetBase* _pChildWidget) {}
	virtual void OnChildItemReleased(UCSUserWidgetBase* _pChildWidget) {}
	virtual void OnChildItemHovered(UCSUserWidgetBase* _pChildWidget) {}
	virtual void OnChildItemUnHovered(UCSUserWidgetBase* _pChildWidget) {}

protected:
	UCSUserWidgetBase* SearchEventParentWidget();

public:
	UFUNCTION() virtual void OnFinishShowAni();
	UFUNCTION() virtual void OnFinishHideAni();

private:
	nUIPanelType::en m_ePanelType = nUIPanelType::Max;
	nBackBtnActionType::en m_eBackBtnActionType = nBackBtnActionType::Max;

protected:
	TWeakObjectPtr<UCSUserWidgetBase> m_pParentWidget = nullptr;
	TWeakObjectPtr<UCSUserWidgetBase> m_pEventParentWidget = nullptr;
	//TWeakObjectPtr<UCSUserWidgetBase> m_pToolTipWidget = nullptr;
};
