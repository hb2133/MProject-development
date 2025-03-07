// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Auth/Credential.h"
#include "UILibrary/Widget/CSWidgetPanel.h"
#include "MProjectWidgetPanel_Lobby.generated.h"

class UCSCanvasPanel;
class UCSButton;
class UMProjectWidget_Tutorial;
class UCSVerticalBox;
class UCSWidgetSwitcher;
class UMProjectWidget_Settings;
class UCSTextBlock;

UCLASS()
class MPROJECT_API UMProjectWidgetPanel_Lobby : public UCSWidgetPanel
{
	GENERATED_BODY()
public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	virtual void Show(ESlateVisibility visible = ESlateVisibility::SelfHitTestInvisible, float fDelayTime = 0.f, float fFadeTime = 0.f, float fDisplayTime = 0.f) override;
public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSCanvasPanel* Canvas_Panel_Start;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSCanvasPanel* Canvas_Panel_Main;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSVerticalBox* VerticalBox_Main;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSVerticalBox* VerticalBox_Play;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Play;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Settings;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Customize;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Exit;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Running;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Digging;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Back;
	UPROPERTY(meta = (BindWidgetOptional))
	UMProjectWidget_Tutorial* W_Tutorial_BP;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSWidgetSwitcher* Switcher_Menu;
	UPROPERTY(meta = (BindWidgetOptional))
	UMProjectWidget_Settings* W_Settings_BP;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Login;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_InApp;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSTextBlock* TextBlock_Login;
public:
	UFUNCTION()
	void OnClick_Play();
	UFUNCTION()
	void OnClick_Settings();
	UFUNCTION()
	void OnClick_Customize();
	UFUNCTION()
	void OnClick_Exit();
	UFUNCTION()
	void OnClick_Running();
	UFUNCTION()
	void OnClick_Digging();
	UFUNCTION()
	void OnClick_Back();
	UFUNCTION()
	void OnClick_InApp();
	UFUNCTION()
	void OnClick_Login();
	void OnTaskOver(bool bArg, FString String);
	//void OnActionOver(EFirebaseAuthError FirebaseAuthError, UUser* User);

private:
	FCredential Credential;
	bool bUsePlayGames = true;
	bool m_bGooglePlayLogin = false;
};
