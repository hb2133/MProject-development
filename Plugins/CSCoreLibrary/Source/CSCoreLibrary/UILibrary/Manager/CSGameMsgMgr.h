// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"
#include "..\Define\CSCommon_GameMsg.h"

#include "UILibrary/Widget/Popup/CSWidget_BasePopup.h"
#include "CSGameMsgMgr.generated.h"

class MsgDataPack
{
public:
	FString Title;
	FString Desc ;
	FString IconName;
	nGameMsgType::en eMsgType;
	nMsgLayerType::en eMsgLayerType;
	nPopupShowButtonType::en m_eShowButtonType;
	CSUIPopupShowValue m_PopupValue;
	MsgDataPack()
	{
		Init();
	}

	void Init()
	{
		Title = TEXT("");
		Desc =  TEXT("");
		eMsgType = nGameMsgType::Max;
		eMsgLayerType = nMsgLayerType::Max;
		m_eShowButtonType = nPopupShowButtonType::Empty;
		m_PopupValue.Init();
	}
};
typedef TSharedPtr<MsgDataPack> MsgDataPackPtr;

class UCSUserWidgetBase;

UCLASS()
class CSCORELIBRARY_API UCSGameMsgMgr : public UCSBaseManager
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void Release() override;
	void Load() override;
	void Tick(float _dt) override;

	
	void ShowMessageBox(const CSUIPopupShowValue& popupValue, float delayTime = 0.0f, bool bHighLayerBox = false);
	bool ShowMessageBox(const FString& _popupTid, UObject* _BindObject = nullptr, FString _FuncName = "");
	

private:
	UCSUserWidgetBase* CreateMessageWidget(nGameMsgType::en eMassageType);
	void ShowMessageWidget(const MsgDataPackPtr messagePack);

private:
	TMap<nGameMsgType::en, TWeakObjectPtr<UCSUserWidgetBase>> m_mapMessageWidget;

};

#define g_GameMsgMgrValid ( g_GameGlobal->IsValidManager<UCSGameMsgMgr>() )
#define g_GameMsgMgr ( g_GameGlobal->GetManager<UCSGameMsgMgr>() )
