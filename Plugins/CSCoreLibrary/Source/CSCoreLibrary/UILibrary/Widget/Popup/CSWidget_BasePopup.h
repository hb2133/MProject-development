// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\..\DataTable\DataRecord\CSPopupRecord.h"
#include "UILibrary/Define/CSCommon_GameMsg.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "CSWidget_BasePopup.generated.h"


class UCSButton;
class UCSImage;
class UCSTextBlock;
DECLARE_DELEGATE_OneParam(BCPopupDelegate, EPopupEventID::en);

class CSUIPopupShowValue
{
public:
	BCPopupDelegate m_Handler;
	nGameMsgType::en m_eMsgType;
	nPopupShowButtonType::en m_eShowButtonType;
	FString m_strTitle;
	FString m_strMsgDesc;
	FString m_strIconName;
	FString m_strOKLocal;
	FString m_strCancelLocal;
	FString m_strBackGroundName;
	FString m_strPrizeBackGroundName;

public:
	CSUIPopupShowValue();
	void Init();
	void Init(CSPopupRecord* _pRecord);	
};


UCLASS()
class CSCORELIBRARY_API UCSWidget_BasePopup: public UCSUserWidgetBase
{
	GENERATED_BODY()
public:
	struct nButton
	{
		enum en
		{
			Ok,
			OkForSingle,
			Cancel,
			Max
		};
	};
	
public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Cancel;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_OK;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_OKForSingle;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSTextBlock* Text_Cancel;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSTextBlock* Text_OK;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSTextBlock* Text_OkForSingle;
	
public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;	
	virtual void Show(ESlateVisibility visible = ESlateVisibility::SelfHitTestInvisible, float fDelayTime = 0.f, float fFadeTime = 0.f, float fDisplayTime = 0.f);
	virtual void Hide(float fDelatTime = 0.f, float fFadeTime = 0.f);


	UFUNCTION() virtual void OnClickedCancel();
	UFUNCTION() virtual void OnClickedOK();

protected:
	virtual void ShowButtons(nPopupShowButtonType::en eButtonType);
	virtual void AllDisableButton();	
public:
	CSUIPopupShowValue m_PopupValue;
	
	void OnClickedOKEvent();
	virtual void OnClickedCancelEvent();

protected:
	UCSButton* m_pButtons[nButton::Max];
};
