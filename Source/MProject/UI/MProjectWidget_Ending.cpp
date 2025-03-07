// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidget_Ending.h"

#include "Kismet/GameplayStatics.h"
#include "MProject/Manager/MPAdMobMgr.h"
#include "MProject/Manager/MProjectMgr.h"
#include "MProject/PlayerCharacter/MProject_Chawracter_Drigger.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"

void UMProjectWidget_Ending::InitData()
{
	Super::InitData();
}

void UMProjectWidget_Ending::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidget_Ending::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(Button_End, &UMProjectWidget_Ending::OnClick_End);
	BIND_BUTTON_EVENT(Button_AdMob, &UMProjectWidget_Ending::OnClick_AdMob);
}

void UMProjectWidget_Ending::UnLinkEvent()
{
	UNBIND_BUTTON_EVENT_ALL(Button_End);
	UNBIND_BUTTON_EVENT_ALL(Button_AdMob);
	
	Super::UnLinkEvent();
}

void UMProjectWidget_Ending::OnClick_End()
{
	UGameplayStatics::OpenLevel(GetWorld(),"Level_MProject");
}

void UMProjectWidget_Ending::OnClick_AdMob()
{
	if (g_MPAdMobMgrValid)
	{
		g_MPAdMobMgr->ShowRewardAd();
	}
}

void UMProjectWidget_Ending::SetResultText()
{
	
}


void UMProjectWidget_Ending::UpdateDriggerResult()
{
	if (g_MProjectMgrValid)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
			if (PlayerCharacter)
			{
				g_MProjectMgr->SetDriggerScore(PlayerCharacter->GetDriggerScoreCount());
				g_MProjectMgr->CreateDriggerScore();
			}
		}
		
		int32 driggerScore = g_MProjectMgr->GetScore();
		TextBlock_Score->SetText(FText::FromString(FString::Printf(TEXT("점수: %d"), driggerScore)));

		FText ratingText = GetDriggerRating(driggerScore);
		TextBlock_Rating->SetText(ratingText);

		FText moneyText = GetDriggerMoney(driggerScore);
		TextBlock_Money->SetText(moneyText);

		FText expText = GetDriggerExp(driggerScore);
		TextBlock_Exp->SetText(expText);
	}
}

FText UMProjectWidget_Ending::GetDriggerRating(int32 score)
{
	if (score >= 1200)
	{
		return FText::FromString(TEXT("전사등급: 특급"));
	}
	else if (score >= 1100)
	{
		return FText::FromString(TEXT("전사등급: 1급"));
	}
	else if (score >= 1000)
	{
		return FText::FromString(TEXT("전사등급: 2급"));
	}
	else if (score >= 900)
	{
		return FText::FromString(TEXT("전사등급: 3급"));
	}

	return FText::FromString(TEXT("전사등급: 미달"));
}

FText UMProjectWidget_Ending::GetDriggerMoney(int32 score)
{
	int32 money = FMath::RoundToInt(score * 0.1f);

	if(g_MProjectMgrValid)
	{
		g_MProjectMgr->SetClearMoney(money);
	}
	
	return FText::FromString(FString::Printf(TEXT("재화: %d"), money));
}

FText UMProjectWidget_Ending::GetDriggerExp(int32 score)
{
	int32 exp = FMath::RoundToInt(score * 0.15f);

	if(g_MProjectMgrValid)
	{
		g_MProjectMgr->SetClearExp(exp);
	}
	
	return FText::FromString(FString::Printf(TEXT("경험치: %d"), exp));
}

void UMProjectWidget_Ending::UpdateRunResult(int32 isSeconds, bool isClear)
{
	if (g_MProjectMgrValid)
	{
		g_MProjectMgr->SetCurrentTime(isSeconds);
		g_MProjectMgr->CreateRunningScore();
		int32 numScore = g_MProjectMgr->GetScore();

		TextBlock_Score->SetText(FText::FromString(FString::Printf(TEXT("점수: %d"), numScore)));

		FText ratingText = GetRunRating(60 - isSeconds, isClear);
		TextBlock_Rating->SetText(ratingText);

		FText moneyText = GetRunMoney(numScore);
		TextBlock_Money->SetText(moneyText);

		FText expText = GetRunExp(numScore);
		TextBlock_Exp->SetText(expText);
	}
}

FText UMProjectWidget_Ending::GetRunRating(int32 remainingTime, bool isClear)
{
	if(isClear)
	{
		if (remainingTime >= 0 && remainingTime <= 50)
		{
			return FText::FromString(TEXT("전사등급: 특급"));
		}
		else if (remainingTime > 50 && remainingTime <= 54)
		{
			return FText::FromString(TEXT("전사등급: 1급"));
		}
		else if (remainingTime > 54 && remainingTime <= 58)
		{
			return FText::FromString(TEXT("전사등급: 2급"));
		}
		else if (remainingTime > 58 && remainingTime <= 60)
		{
			return FText::FromString(TEXT("전사등급: 3급"));
		}
	}
	else
	{
		return FText::FromString(TEXT("전사등급: 미달"));
	}
	
	return FText::FromString(TEXT("전사등급: 미달"));
}

FText UMProjectWidget_Ending::GetRunMoney(int32 score)
{
	int32 money = FMath::RoundToInt(score * 0.1f);

	if(g_MProjectMgrValid)
	{
		g_MProjectMgr->SetClearMoney(money);
	}
	
	return FText::FromString(FString::Printf(TEXT("재화: %d"), money));
}

FText UMProjectWidget_Ending::GetRunExp(int32 score)
{
	int32 exp = FMath::RoundToInt(score * 0.15f);

	if(g_MProjectMgrValid)
	{
		g_MProjectMgr->SetClearExp(exp);
	}
	
	return FText::FromString(FString::Printf(TEXT("경험치: %d"), exp));
}