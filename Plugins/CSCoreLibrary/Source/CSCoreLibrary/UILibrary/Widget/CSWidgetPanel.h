// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "CSWidgetPanel.generated.h"

 class UCSWidget_MenuUnderBar;
UCLASS()
class CSCORELIBRARY_API UCSWidgetPanel : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void Show(ESlateVisibility visible = ESlateVisibility::SelfHitTestInvisible, float fDelayTime = 0.f, float fFadeTime = 0.f, float fDisplayTime = 0.f);
	virtual void Hide(float fDelatTime = 0.f, float fFadeTime = 0.f);
	virtual void Clear();

public:
	virtual void OnClicked_Close() {;}
};
