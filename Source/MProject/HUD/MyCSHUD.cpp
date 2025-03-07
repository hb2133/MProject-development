// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCSHUD.h"
#include "UILibrary/Manager/CSUIMgr.h"

void AMyCSHUD::CreateWidgetPanels()
{
	if(g_UIMgrValid)
	{
		g_UIMgr->ClearPanels();

		TArray<SPanelTypeInfo> _Infos;
		_Infos.Add(SPanelTypeInfo(nUIPanelType::Main, FName("Main")));
		_Infos.Add(SPanelTypeInfo(nUIPanelType::Lobby, FName("Lobby")));
		_Infos.Add(SPanelTypeInfo(nUIPanelType::InApp, FName("InApp")));
		_Infos.Add(SPanelTypeInfo(nUIPanelType::GameRunning, FName("GameRunning")));
		_Infos.Add(SPanelTypeInfo(nUIPanelType::GameDigging, FName("GameDigging")));
		_Infos.Add(SPanelTypeInfo(nUIPanelType::Customize, FName("Customize")));
		

		g_UIMgr->CreatePanels(_Infos, GetWorld());
	}
}
		