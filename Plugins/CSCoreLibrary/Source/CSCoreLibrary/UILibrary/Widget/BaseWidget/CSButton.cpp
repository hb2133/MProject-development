// Fill out your copyright notice in the Description page of Project Settings.


#include "CSButton.h"

#include "CoreLibrary/GameGlobal/CSGameGlobal.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"

void UCSButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	FButtonStyle style;
	style.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
	style.Hovered.DrawAs = ESlateBrushDrawType::NoDrawType;
	style.Pressed.DrawAs = ESlateBrushDrawType::NoDrawType;
	style.SetNormalPadding(FMargin(0,0,0,0));
	style.SetPressedPadding(FMargin(0,0,0,0));
	
	SetStyle(style);
}

TSharedRef<SWidget> UCSButton::RebuildWidget()
{
	if(OnClicked.IsAlreadyBound(this,&UCSButton::OnClick_Sound))
	{
		OnClicked.RemoveDynamic(this,&UCSButton::OnClick_Sound);
	}
	OnClicked.AddDynamic(this,&UCSButton::OnClick_Sound);
	
	return Super::RebuildWidget();
}

void UCSButton::OnClick_Sound()
{
	if(g_SoundMgrValid)
	{
		if(m_strBtnSound != "")
		{
			g_SoundMgr->ButtonPlaySound(m_fPlayTime,m_strBtnSound);
		}
	}
}

