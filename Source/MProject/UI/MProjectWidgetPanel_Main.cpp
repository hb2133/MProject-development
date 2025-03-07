// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidgetPanel_Main.h"

#include "MProjectWidget_Running.h"
#include "MProjectWidget_Tutorial.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "Sound/SoundBase.h"
#include "UILibrary/Manager/CSUIMgr.h"

void UMProjectWidgetPanel_Main::InitData()
{
	Super::InitData();			
}

void UMProjectWidgetPanel_Main::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidgetPanel_Main::LinkEvent()
{
	Super::LinkEvent();
	BIND_BUTTON_EVENT(Button_Start, &UMProjectWidgetPanel_Main::OnClick_Start);
	
}

void UMProjectWidgetPanel_Main::UnLinkEvent()
{
	UNBIND_BUTTON_EVENT_ALL(Button_Start);
	Super::UnLinkEvent();	
}

void UMProjectWidgetPanel_Main::OnClick_Start()
{
	if(g_UIMgrValid)
		g_UIMgr->ShowUIPanel(nUIPanelType::Lobby);
	/*
	
	if(Canvas_Panel_Start)
	{
		Canvas_Panel_Start->SetVisibility(ESlateVisibility::Collapsed);
	}
	if(Canvas_Panel_Main)
	{
		Canvas_Panel_Main->SetVisibility(ESlateVisibility::Visible);
		VerticalBox_Main->SetVisibility(ESlateVisibility::Visible);
	}
	*/
}
