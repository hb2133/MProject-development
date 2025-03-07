// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidgetPanel_Lobby.h"

#include "MProjectWidget_Running.h"
#include "MProjectWidget_Tutorial.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MProject/Define/MPCommon.h"
#include "MProject/Manager/MProjectMgr.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "UILibrary/Widget/BaseWidget/CSVerticalBox.h"
#include "Sound/SoundBase.h"
#include "UILibrary/Define/CSCommon_GameMsg.h"
#include "UILibrary/Manager/CSUIMgr.h"
#include "UILibrary/Widget/BaseWidget/CSWidgetSwitcher.h"
#include "MProjectWidget_Settings.h"
#include "Auth/Auth.h"
#include "Auth/Credential.h"
#include "Google/GoogleServices.h"
#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"

void UMProjectWidgetPanel_Lobby::InitData()
{
	Super::InitData();
}

void UMProjectWidgetPanel_Lobby::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidgetPanel_Lobby::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(Button_Play, &UMProjectWidgetPanel_Lobby::OnClick_Play);
	BIND_BUTTON_EVENT(Button_Settings, &UMProjectWidgetPanel_Lobby::OnClick_Settings);
	BIND_BUTTON_EVENT(Button_Customize, &UMProjectWidgetPanel_Lobby::OnClick_Customize);
	BIND_BUTTON_EVENT(Button_Exit, &UMProjectWidgetPanel_Lobby::OnClick_Exit);
	BIND_BUTTON_EVENT(Button_Running, &UMProjectWidgetPanel_Lobby::OnClick_Running);
	BIND_BUTTON_EVENT(Button_Digging, &UMProjectWidgetPanel_Lobby::OnClick_Digging);
	BIND_BUTTON_EVENT(Button_Back, &UMProjectWidgetPanel_Lobby::OnClick_Back);
	BIND_BUTTON_EVENT(Button_Login, &UMProjectWidgetPanel_Lobby::OnClick_Login);
	BIND_BUTTON_EVENT(Button_InApp, &UMProjectWidgetPanel_Lobby::OnClick_InApp);
}

void UMProjectWidgetPanel_Lobby::UnLinkEvent()
{
	Super::UnLinkEvent();
	UNBIND_BUTTON_EVENT_ALL(Button_Play);
	UNBIND_BUTTON_EVENT_ALL(Button_Settings);
	UNBIND_BUTTON_EVENT_ALL(Button_Customize);
	UNBIND_BUTTON_EVENT_ALL(Button_Exit);
	UNBIND_BUTTON_EVENT_ALL(Button_Running);
	UNBIND_BUTTON_EVENT_ALL(Button_Digging);
	UNBIND_BUTTON_EVENT_ALL(Button_Back);
	UNBIND_BUTTON_EVENT_ALL(Button_InApp);
}

void UMProjectWidgetPanel_Lobby::Show(ESlateVisibility visible, float fDelayTime, float fFadeTime, float fDisplayTime)
{
	Super::Show(visible, fDelayTime, fFadeTime, fDisplayTime);
}

void UMProjectWidgetPanel_Lobby::OnClick_Back()
{	
	if(g_UIMgrValid)
	{
		if(Switcher_Menu)
		{
			if(Switcher_Menu->GetActiveWidgetIndex() ==  nMenuState::Main)
			{
				g_UIMgr->HideUIPanel(nUIPanelType::Lobby);
				g_UIMgr->ShowUIPanel(nUIPanelType::Main);
				
			}
			Switcher_Menu->SetActiveWidgetIndex(nMenuState::Main);
		}
	}
}

void UMProjectWidgetPanel_Lobby::OnClick_Play()
{
	if(Switcher_Menu)
		Switcher_Menu->SetActiveWidgetIndex(nMenuState::Play);
}

void UMProjectWidgetPanel_Lobby::OnClick_Settings()
{
	if(W_Settings_BP)
		W_Settings_BP->Show();
}

void UMProjectWidgetPanel_Lobby::OnClick_Customize()
{	
	if(g_UIMgrValid)
	{
		g_UIMgr->HideUIPanel(nUIPanelType::Lobby);
		g_UIMgr->ShowUIPanel(nUIPanelType::Customize);
	}
}

void UMProjectWidgetPanel_Lobby::OnClick_Exit()
{
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
	}
}

void UMProjectWidgetPanel_Lobby::OnClick_Running()
{	
	if (Canvas_Panel_Main)
	{
		Canvas_Panel_Main->SetVisibility(ESlateVisibility::Collapsed);
	}
	if(g_UIMgrValid)
		g_UIMgr->HideUIPanel(nUIPanelType::Main);

	if (W_Tutorial_BP)
	{
		W_Tutorial_BP->Show();
	}

	if(g_SoundMgrValid)
	{
		g_SoundMgr->Stop();
		g_SoundMgr->PlaySound2D("Sound_Background_1_Cue");
	}
}


void UMProjectWidgetPanel_Lobby::OnClick_Digging()
{	
	UGameplayStatics::OpenLevel(GetWorld(),"Level_MProject2");
}

void UMProjectWidgetPanel_Lobby::OnClick_InApp()
{
	if(g_UIMgrValid)
		g_UIMgr->ShowUIPanel(nUIPanelType::InApp);
}

void UMProjectWidgetPanel_Lobby::OnClick_Login()
{
	FString FirebaseLink = g_CSDefineRecordMgr->GetValue_String("firebase_link");

	if (FirebaseLink.IsEmpty())
	{
		TextBlock_Login->SetText(FText::FromString("ServerClientID is missing!"));
		return;
	}

	UGoogleServicesLibrary::SignIn(FirebaseLink, false, false, bUsePlayGames, FGoogleSignInCallback::CreateUObject(this, &ThisClass::OnTaskOver));
}

void UMProjectWidgetPanel_Lobby::OnTaskOver(bool bArg, FString String)
{
	if (!bArg)
	{
		TextBlock_Login->SetText(FText::FromString("1"));
		return;
	}

	if (!bUsePlayGames)
	{
		// Standard Google Sign-In
		FString IdToken = UGoogleServicesLibrary::GetIdToken();
		FString AccessToken = UGoogleServicesLibrary::GetAccessToken();

		if (IdToken.IsEmpty() || AccessToken.IsEmpty())
		{
			return;
		}

		Credential = UCredentialLibrary::GetCredentialFromGoogle(IdToken, AccessToken);
	}
	else
	{
		// Google Play Games Sign-In
		FString ServerAuthCode = UGoogleServicesLibrary::GetServerAuthCode();
		
		if (ServerAuthCode.IsEmpty())
		{
			if (!m_bGooglePlayLogin)
			{
				TextBlock_Login->SetText(FText::FromString("2"));
				m_bGooglePlayLogin = true;
			}
		}
		else
		{
			TextBlock_Login->SetText(FText::FromString("3"));
			Credential = UCredentialLibrary::GetCredentialFromPlayGames(ServerAuthCode);
		}
	}
}
