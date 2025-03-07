// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidget_Tutorial.h"

#include "MProjectWidget_Running.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "Kismet/GameplayStatics.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"

void UMProjectWidget_Tutorial::InitData()
{
	Super::InitData();
	m_bVideoReset = true;
}

void UMProjectWidget_Tutorial::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidget_Tutorial::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(Button_Start, &UMProjectWidget_Tutorial::OnClick_Start);
}

void UMProjectWidget_Tutorial::UnLinkEvent()
{
	Super::UnLinkEvent();
	UNBIND_BUTTON_EVENT_ALL(Button_Start);
}

void UMProjectWidget_Tutorial::OnClick_Start()
{
	PlaySoundButton();
	
	if(Canvas_Panel && W_Running_BP&&W_DriggerBP)
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		Canvas_Panel->SetVisibility(ESlateVisibility::Collapsed);
		if (CurrentLevelName == "Level_MProject")
		{
			W_Running_BP->SetVisibility(ESlateVisibility::Visible);
		}
		else if(CurrentLevelName == "Level_MProject2")
		{
			W_DriggerBP->SetVisibility(ESlateVisibility::Visible);
		}
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// PlayerCharacter를 가져옴
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			AActor* NewViewTarget = PlayerPawn;
			PlayerController->SetViewTargetWithBlend(NewViewTarget, 1.0f);
		}
	}

	m_bVideoReset = false;
}

void UMProjectWidget_Tutorial::PlaySoundButton()
{
	if(g_SoundMgrValid)
	{
		g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Button_Cue");
	}
}