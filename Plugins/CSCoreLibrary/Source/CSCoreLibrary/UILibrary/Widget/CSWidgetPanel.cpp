// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidgetPanel.h"

void UCSWidgetPanel::Show(ESlateVisibility visible /*=ESlateVisibility::SelfHitTestInvisible*/, float fDelayTime /*=0.f*/, float fFadeTime /*=0.f*/, float fDisplayTime /*=0.f*/)
{
	Super::Show(visible, fDelayTime, fFadeTime, fDisplayTime);
}

void UCSWidgetPanel::Hide(float fDelatTime /*=0.f*/, float fFadeTime /*=0.f*/)
{
	Super::Hide(fDelatTime, fFadeTime);
	Clear();
}

void UCSWidgetPanel::Clear()
{
	
}
