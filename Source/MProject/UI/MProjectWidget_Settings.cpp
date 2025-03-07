// Fill out your copyright notice in the Description page of Project Settings.

#include "MProjectWidget_Settings.h"

#include "MProjectWidget_Running.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"

inline void UMProjectWidget_Settings::InitData()
{
	Super::InitData();

	m_strMuteImgName = "SPR_Volume_Off";
	m_strUnmuteImgName = "SPR_Volume_On";
}

inline void UMProjectWidget_Settings::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

inline void UMProjectWidget_Settings::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(ButtonStart, &UMProjectWidget_Settings::OnStartButtonClicked);
	SliderBGM->OnValueChanged.AddDynamic(this,&UMProjectWidget_Settings::OnBGMVolumeChanged);
	SliderBtn->OnValueChanged.AddDynamic(this,&UMProjectWidget_Settings::OnBtnVolumeChanged);
	BIND_BUTTON_EVENT(ButtonMuteBGM, &UMProjectWidget_Settings::OnMuteBGMButtonClicked);
	BIND_BUTTON_EVENT(ButtonMuteBtn, &UMProjectWidget_Settings::OnMuteBtnButtonClicked);
}

inline void UMProjectWidget_Settings::UnLinkEvent()
{
	UNBIND_BUTTON_EVENT_ALL(ButtonStart);
	SliderBGM->OnValueChanged.RemoveAll(this);
	SliderBtn->OnValueChanged.RemoveAll(this);
	UNBIND_BUTTON_EVENT_ALL(ButtonMuteBGM);
	UNBIND_BUTTON_EVENT_ALL(ButtonMuteBtn);

	Super::UnLinkEvent();
}

void UMProjectWidget_Settings::OnStartButtonClicked()
{
	Hide();
}

void UMProjectWidget_Settings::OnBGMVolumeChanged(float BGMVolume)
{
	m_BGMVolume = BGMVolume;
	
	if (g_SoundMgrValid && !g_SoundMgr->GetIsBGMMute())
	{
		g_SoundMgr->SetBGMVolume(BGMVolume);
	}
}

void UMProjectWidget_Settings::OnBtnVolumeChanged(float BtnVolume)
{
	m_BtnVolume = BtnVolume;

	if (g_SoundMgrValid && !g_SoundMgr->GetIsBtnMute())
	{
		g_SoundMgr->SetBtnVolume(BtnVolume);
	}
}

void UMProjectWidget_Settings::OnMuteBGMButtonClicked()
{
	if (ButtonMuteBGM && g_SoundMgrValid)
	{
		if (g_SoundMgr->GetIsBGMMute())
		{
			g_SoundMgr->SetBGMMute(false);
			g_SoundMgr->SetBGMVolume(m_BGMVolume);

			ImgMuteBGM->SetBrushFromSpriteName(m_strUnmuteImgName);
		}
		else
		{
			g_SoundMgr->SetBGMMute(true);

			ImgMuteBGM->SetBrushFromSpriteName(m_strMuteImgName);
		}
	}
}

void UMProjectWidget_Settings::OnMuteBtnButtonClicked()
{
	if (ButtonMuteBtn && g_SoundMgrValid)
	{
		if (g_SoundMgr->GetIsBtnMute())
		{
			g_SoundMgr->SetBtnMute(false);
			g_SoundMgr->SetBtnVolume(m_BtnVolume);

			ImgMuteBtn->SetBrushFromSpriteName(m_strUnmuteImgName);
		}
		else
		{
			g_SoundMgr->SetBtnMute(true);

			ImgMuteBtn->SetBrushFromSpriteName(m_strMuteImgName);
		}
	}
}


