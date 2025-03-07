// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidgetSwitcher.h"
#include "UILibrary/Widget/CSWidgetPanel.h"

void UCSWidgetSwitcher::SetActiveWidgetIndex(int32 Index)
{
	this->ShowActiveWidgetPanel(false);

	Super::SetActiveWidgetIndex(Index);

	this->ShowActiveWidgetPanel(true);
}

void UCSWidgetSwitcher::SetActiveWidget(UWidget* Widget)
{
	this->ShowActiveWidgetPanel(false);

	Super::SetActiveWidget(Widget);

	this->ShowActiveWidgetPanel(true);
}

void UCSWidgetSwitcher::ShowActiveWidgetPanel(bool _bShow)
{
	if (UCSWidgetPanel* _pPanel = ::Cast<UCSWidgetPanel>(GetActiveWidget()))
	{
		_bShow ? _pPanel->Show(ESlateVisibility::SelfHitTestInvisible) : _pPanel->Hide();
	}
}