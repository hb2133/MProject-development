// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidget_Running.h"

#include "MProjectWidget_Ending.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "Kismet/GameplayStatics.h"
#include "MProject/Manager/MProjectMgr.h"
#include "MProject/PlayerCharacter/MProject_Character.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"

void UMProjectWidget_Running::InitData()
{
	Super::InitData();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Character* PlayerCharacter = Cast<AMProject_Character>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			PlayerCharacter->OnPlayerHPChanged.AddDynamic(this, &UMProjectWidget_Running::UpdateHPLog);
			PlayerCharacter->OnPlayerScoreChanged.AddDynamic(this, &UMProjectWidget_Running::UpdateScoreLog);
			PlayerCharacter->OnPlayerClear.AddDynamic(this, &UMProjectWidget_Running::ClearLog);
		}
	}

	Warning_EndDelegate.BindDynamic(this,&UMProjectWidget_Running::Warning_AnimationFinished);
	BindToAnimationFinished(Warning_Animation,Warning_EndDelegate);
	
	TestClickNum1 = 0;
	TestClickNum2 = 0;
	TestClickNum3 = 0;

	bIsRedPressed = false;
	bIsGreenPressed = false;
	bIsBluePressed = false;

	m_iSeconds  = 60;
	Milliseconds = 0;
	bIsTimerActive = false;
}

void UMProjectWidget_Running::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 키보드 입력 체크
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// Q 키가 눌렸을 때 Button_R에 대응
		if (PlayerController->IsInputKeyDown(EKeys::Q))
		{
			if (!bIsRedPressed)  // 키가 처음 눌렸을 때만 실행
				{
				OnClick_R();
				bIsRedPressed = true;
				}
		}
		else if (bIsRedPressed)  // 키가 떼졌을 때
			{
			OnPressed_R();
			bIsRedPressed = false;
			}

		// W 키가 눌렸을 때 Button_G에 대응
		if (PlayerController->IsInputKeyDown(EKeys::W))
		{
			if (!bIsGreenPressed)
			{
				OnClick_G();
				bIsGreenPressed = true;
			}
		}
		else if (bIsGreenPressed)
		{
			OnPressed_G();
			bIsGreenPressed = false;
		}

		// E 키가 눌렸을 때 Button_B에 대응
		if (PlayerController->IsInputKeyDown(EKeys::E))
		{
			if (!bIsBluePressed)
			{
				OnClick_B();
				bIsBluePressed = true;
			}
		}
		else if (bIsBluePressed)
		{
			OnPressed_B();
			bIsBluePressed = false;
		}
	}

	//타이머
	if (bIsTimerActive && m_iSeconds >= 0)
	{
		AccumulatedTime += InDeltaTime * 1000;

		while (AccumulatedTime >= 10)
		{
			AccumulatedTime -= 10;
			Milliseconds -= 1;

			if (Milliseconds < 0)
			{
				Milliseconds = 99;
				m_iSeconds--;

				if (m_iSeconds < 0)
				{
					OnTimerFinished();
					return;
				}
			}
		}

		FString TimeText = FString::Printf(TEXT("%02d:%02d"), m_iSeconds, Milliseconds);
		if (TextBlock_Timer)
		{
			TextBlock_Timer->SetText(FText::FromString(TimeText));

			if (m_iSeconds <= 10)
			{
				TextBlock_Timer->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			}
			else
			{
				TextBlock_Timer->SetColorAndOpacity(FSlateColor(FLinearColor::White));
			}
		}
	}
}

void UMProjectWidget_Running::LinkEvent()
{
	Super::LinkEvent();
	
	Button_R->OnPressed.AddDynamic(this, &UMProjectWidget_Running::OnClick_R);
	Button_R->OnReleased.AddDynamic(this, &UMProjectWidget_Running::OnPressed_R);
	Button_G->OnPressed.AddDynamic(this, &UMProjectWidget_Running::OnClick_G);
	Button_G->OnReleased.AddDynamic(this, &UMProjectWidget_Running::OnPressed_G);
	Button_B->OnPressed.AddDynamic(this, &UMProjectWidget_Running::OnClick_B);
	Button_B->OnReleased.AddDynamic(this, &UMProjectWidget_Running::OnPressed_B);
	BIND_BUTTON_EVENT(Button_GameClear, &UMProjectWidget_Running::OnClick_GameClear);
	BIND_BUTTON_EVENT(Button_EXIT, &UMProjectWidget_Running::OnClick_EXIT);
}

void UMProjectWidget_Running::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMProjectWidget_Running::OnClick_R()
{
	bIsTimerActive = true; // 타이머 시작
	bIsRedPressed = true;
	TestClickNum1 += 1;  // 클릭 수 증가
	UpdateButtonState(TextBock_TestNum1, TestClickNum1);
}

void UMProjectWidget_Running::OnPressed_R()
{
	bIsRedPressed = false;
}

void UMProjectWidget_Running::OnClick_G()
{
	bIsTimerActive = true; // 타이머 시작
	bIsGreenPressed = true;
	TestClickNum2 += 1;  // 클릭 수 증가
	UpdateButtonState(TextBock_TestNum2, TestClickNum2);
}

void UMProjectWidget_Running::OnPressed_G()
{
	bIsGreenPressed = false;
}

void UMProjectWidget_Running::OnClick_B()
{
	bIsTimerActive = true; // 타이머 시작
	bIsBluePressed = true;
	TestClickNum3 += 1;  // 클릭 수 증가
	UpdateButtonState(TextBock_TestNum3, TestClickNum3);
}

void UMProjectWidget_Running::OnPressed_B()
{
	bIsBluePressed = false;
}

void UMProjectWidget_Running::OnClick_GameClear()
{
	if(W_Ending_BP)
	{
		W_Ending_BP->UpdateRunResult(m_iSeconds, bIsClear);
		W_Ending_BP->Show();
	}
}

void UMProjectWidget_Running::OnClick_EXIT()
{
	OnClickBackLevel();
}


void UMProjectWidget_Running::UpdateButtonState(UCSTextBlock* testnum, int32 clicknum)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Character* PlayerCharacter = Cast<AMProject_Character>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			PlayerCharacter->SetButtonPressed(bIsRedPressed, bIsGreenPressed, bIsBluePressed);
		}
	}

	// 클릭 수를 UI에 반영
	if (testnum)
	{
		testnum->SetText(FText::AsNumber(clicknum));
	}
}

void UMProjectWidget_Running::UpdateHPLog(int32 NewHP)
{
	switch (NewHP)
	{
	case 2:
		if(g_SoundMgrValid)
		{
			g_SoundMgr->Stop();
			g_SoundMgr->ButtonPlaySound(0.0f, "Sound_RunMiss_Cue");
		}
		if(Image_Health3)
			Image_Health3->SetBrushFromSpriteName("SPR_Energy0_Image");
		Warning_AnimationPlay();
		
		break;
	case 1:
		if(g_SoundMgrValid)
		{
			g_SoundMgr->Stop();
			g_SoundMgr->ButtonPlaySound(0.0f, "Sound_RunMiss_Cue");
		}
		if(Image_Health2)
			Image_Health2->SetBrushFromSpriteName("SPR_Energy0_Image");
		Warning_AnimationPlay();
		break;
	case 0:
		if(Image_Health1)
			Image_Health1->SetBrushFromSpriteName("SPR_Energy0_Image");
		if(Image_GameClear && Canvas_GameClear)
		{
			if(g_SoundMgrValid)
			{
				g_SoundMgr->Stop();
				g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Fail3_Cue");
			}
			Image_GameClear->SetBrushFromSpriteName("SPR_Fail_Image");
			Canvas_GameClear->SetVisibility(ESlateVisibility::Visible);
			Button_GameClear->SetVisibility(ESlateVisibility::Collapsed);
			bIsTimerActive = false;
			bIsClear = false;
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMProjectWidget_Running::OnDelayedAnimationPlay, 3.0f, true);
		}
		break;
		default:
			break;
	}
}

void UMProjectWidget_Running::UpdateScoreLog(int32 NewScore)
{
	switch (NewScore)
	{
	case 0:
		TextBlock_Score->SetText(FText::FromString(TEXT("0/3")));
		break;
	case 1:
		TextBlock_Score->SetText(FText::FromString(TEXT("1/3")));
		break;
	case 2:
		TextBlock_Score->SetText(FText::FromString(TEXT("2/3")));
		break;
	case 3:
		TextBlock_Score->SetText(FText::FromString(TEXT("3/3")));
		break;
	default:
		break;
	}
}


void UMProjectWidget_Running::Warning_AnimationPlay()
{
	if(Image_Warning && Warning_Animation)
	{
		Image_Warning->SetBrushFromSpriteName("SPR_OverlapError_Image");
		Image_Warning->SetVisibility(ESlateVisibility::Visible);
	
		PlayAnimation(Warning_Animation,0.0f);
	}
}

void UMProjectWidget_Running::Warning_AnimationFinished()
{
	if(Image_Warning)
	{
		Image_Warning->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMProjectWidget_Running::OnTimerFinished()
{
	bIsTimerActive = false;
	m_iSeconds = 0;
	Milliseconds = 0;
	TextBlock_Timer->SetText(FText::FromString("00:00"));

	if(Image_GameClear && Canvas_GameClear && Button_GameClear)
	{
		Image_GameClear->SetBrushFromSpriteName("SPR_Fail_Image");
		Canvas_GameClear->SetVisibility(ESlateVisibility::Visible);
		Button_GameClear->SetVisibility(ESlateVisibility::Collapsed);
		if(g_SoundMgrValid)
		{
			g_SoundMgr->Stop();
			g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Fail3_Cue");
		}
		bIsClear = false;
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMProjectWidget_Running::OnDelayedAnimationPlay, 3.0f, true);

	UE_LOG(LogTemp, Log, TEXT("Timer finished!"));
}
void UMProjectWidget_Running::OnDelayedAnimationPlay()
{
	if(Button_GameClear)
		Button_GameClear->SetVisibility(ESlateVisibility::Visible);
	TouchText_AnimationPlay();
}

void UMProjectWidget_Running::TouchText_AnimationPlay()
{
	if(TouchText_Animation)
	{
		PlayAnimation(TouchText_Animation, 0.0f);
	}
}

void UMProjectWidget_Running::ClearLog()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Character* PlayerCharacter = Cast<AMProject_Character>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			if(PlayerCharacter->GetGameClear() == true)
			{
				if(Image_GameClear && Canvas_GameClear && Button_GameClear)
				{
					Image_GameClear->SetBrushFromSpriteName("SPR_Clear_Image");
					Canvas_GameClear->SetVisibility(ESlateVisibility::Visible);
					Button_GameClear->SetVisibility(ESlateVisibility::Collapsed);
					bIsTimerActive = false;
					
					if(g_SoundMgrValid)
					{
						g_SoundMgr->Stop();
						g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Clear_Cue");
					}

					bIsClear = true;
					
					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMProjectWidget_Running::OnDelayedAnimationPlay, 3.0f, true);
				}
			}
		}
	}
}

void UMProjectWidget_Running::OnClickBackLevel()
{
	if(g_SoundMgrValid)
	{
		g_SoundMgr->Stop();
		g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Button_Cue");
	}
	UGameplayStatics::OpenLevel(GetWorld(),"Level_MProject");
}