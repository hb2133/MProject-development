// Fill out your copyright notice in the Description page of Project Settings.

#include "MProjectWidget_CustomizePreview.h"
#include "MPWidget_PreviewItem.h"

#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Manager/CSUIMgr.h"
#include "UILibrary/Widget/BaseWidget/CSScrollBox.h"

void UMProjectWidget_CustomizePreview::InitData()
{
	Super::InitData();

	if (PreviewItem)
	{
		PreviewItem->SetParentWidget(this);
	}
}

void UMProjectWidget_CustomizePreview::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidget_CustomizePreview::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(ButtonExit, &UMProjectWidget_CustomizePreview::OnExitButtonClicked);
}

void UMProjectWidget_CustomizePreview::UnLinkEvent()
{
	UNBIND_BUTTON_EVENT_ALL(ButtonExit);
	
	Super::UnLinkEvent();
}

void UMProjectWidget_CustomizePreview::OnExitButtonClicked()
{
	if(g_UIMgrValid)
	{
		OnChildItemClicked(this);
		g_UIMgr->HideUIPanel(nUIPanelType::Customize);
		g_UIMgr->ShowUIPanel(nUIPanelType::Lobby);
	}
}
