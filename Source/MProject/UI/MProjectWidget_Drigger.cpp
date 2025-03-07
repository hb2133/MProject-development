// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidget_Drigger.h"

#include "EngineUtils.h"
#include "MProjectWidget_Ending.h"
#include "ActorLibrary/Actor/Component/ActorComponent/CSStaticMeshComponent.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MProject/Manager/MProjectMgr.h"
#include "MProject/PlayerCharacter/MProject_Chawracter_Drigger.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"
#include "UILibrary/Widget/BaseWidget/CSCanvasPanel.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"

void UMProjectWidget_Drigger::InitData()
{
	Super::InitData();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			// 바인딩 시도 및 디버깅 로그 추가
			PlayerCharacter->OnDriggerPlayerHPChanged.AddDynamic(this, &UMProjectWidget_Drigger::UpdateDiggerHPLog);
			PlayerCharacter->OnDriggerPlayerScoreChanged.AddDynamic(this, &UMProjectWidget_Drigger::UpdateDiggerScoreLog);
		}
	}

	Warning_EndDelegate.BindDynamic(this,&UMProjectWidget_Drigger::Warning_AnimationFinished);
	BindToAnimationFinished(Warning_Animation,Warning_EndDelegate);
	
	Seconds  = 60;
	Milliseconds = 0;
	bIsTimerActive = false;
}

void UMProjectWidget_Drigger::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//임시 키보드 입력 받기
	// 키보드 입력 체크
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// Q 키가 눌렸을 때 Button_R에 대응
		if (PlayerController->IsInputKeyDown(EKeys::Q))
		{
			OnClick_R();
		}
		else if(PlayerController->IsInputKeyDown(EKeys::W))
		{
			OnClick_G();
		}
		else if(PlayerController->IsInputKeyDown(EKeys::E))
		{
			OnClick_B();
		}
	}

	if (bIsTimerActive && Seconds >= 0)
	{
		AccumulatedTime += InDeltaTime * 1000;

		while (AccumulatedTime >= 10)
		{
			AccumulatedTime -= 10;
			Milliseconds -= 1;

			if (Milliseconds < 0)
			{
				Milliseconds = 99;
				Seconds--;

				// 10초 이하일 때 초가 변경될 때마다 TimerSound 실행
				if (Seconds <= 10 && Milliseconds == 99)
				{
					if(g_SoundMgrValid)
					{
						g_SoundMgr->Stop();
						g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Time_Cue");
					}
				}
				
				if (Seconds < 0)
				{
					OnTimerFinished();
					return;
				}
			}
		}

		FString TimeText = FString::Printf(TEXT("%02d:%02d"), Seconds, Milliseconds);
		if (TextBlock_Timer)
		{
			TextBlock_Timer->SetText(FText::FromString(TimeText));

			if (Seconds <= 10)
			{
				TextBlock_Timer->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			}
			else
			{
				TextBlock_Timer->SetColorAndOpacity(FSlateColor(FLinearColor::White));
			}
		}
	}

	
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			if(FoundActor)
			{
				if (PlayerCharacter->State == EState::Digging)
				{

					FoundActor->SetActorLocation(PlayerCharacter->GetMesh()->GetSocketLocation("Drigger_Hand_L"));
					FoundActor->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(FoundActor->GetActorLocation(), PlayerCharacter->GetMesh()->GetSocketLocation("Hand_RS")));
				}
				else
				{
					FoundActor->SetActorLocation(FVector(1200.0f,10.0f,-50.0f));
				}
			}
		}
	}
}

void UMProjectWidget_Drigger::LinkEvent()
{
	Super::LinkEvent();

	BIND_BUTTON_EVENT(Button_R, &UMProjectWidget_Drigger::OnClick_R);
	BIND_BUTTON_EVENT(Button_G, &UMProjectWidget_Drigger::OnClick_G);
	BIND_BUTTON_EVENT(Button_B, &UMProjectWidget_Drigger::OnClick_B);
	BIND_BUTTON_EVENT(Button_GameClear, &UMProjectWidget_Drigger::OnClick_GameClear);
	BIND_BUTTON_EVENT(Button_EXIT, &UMProjectWidget_Drigger::OnClick_EXIT);
}

void UMProjectWidget_Drigger::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UMProjectWidget_Drigger::OnClick_R()
{
	bIsTimerActive = true;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			if (PlayerCharacter->State == EState::Idle)
			{
				PlayerCharacter->State = EState::Digging;
				if (PlayerCharacter->State == EState::Digging)
				{
					FoundActor = nullptr;
					for (TActorIterator<AActor> It(GetWorld(), AActor::StaticClass()); It; ++It)
					{
						if (It->GetClass()->GetName().Contains("Digger_BP"))
						{
							FoundActor = *It;
							break;
						}
					}
				}
			}
		}
	}
}

void UMProjectWidget_Drigger::OnClick_G()
{
	bIsTimerActive = true; // 타이머 시작
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			if(PlayerCharacter->State == EState::Idle)
			{
				PlayerCharacter->State = EState::Pick;
				if (PlayerCharacter->State == EState::Pick)
				{
					if (PlayerCharacter->StaticMeshComponent)
					{
						UStaticMesh* NewMesh = g_FileMgr->LoadObject<UStaticMesh>(nResourceType::General, TEXT("Pick"));
						if (NewMesh)
						{
							PlayerCharacter->StaticMeshComponent->SetStaticMesh(NewMesh);
							PlayerCharacter->StaticMeshComponent->SetHiddenInGame(false);
							if (PlayerCharacter->GetMesh())
							{
								// 소켓 이름 설정 (스켈레탈 메쉬의 소켓 이름)
								FName SocketName = TEXT("Hand_L_Pick"); // 적절한 소켓 이름으로 변경
								PlayerCharacter->StaticMeshComponent->AttachToComponent(
									PlayerCharacter->GetMesh(),
									FAttachmentTransformRules::SnapToTargetIncludingScale,
									SocketName
								);
							}
						}
					}
				}
			}
		}
	}
}
void UMProjectWidget_Drigger::OnClick_B()
{
	bIsTimerActive = true; // 타이머 시작
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			if(PlayerCharacter->State == EState::Idle)
			{
				PlayerCharacter->State = EState::Drill;
				if (PlayerCharacter->State == EState::Drill)
				{
					if (PlayerCharacter->StaticMeshComponent)
					{
						UStaticMesh* NewMesh = g_FileMgr->LoadObject<UStaticMesh>(nResourceType::General, TEXT("Drill"));
						if (NewMesh)
						{
							PlayerCharacter->StaticMeshComponent->SetStaticMesh(NewMesh);
							PlayerCharacter->StaticMeshComponent->SetHiddenInGame(false);
							if (PlayerCharacter->GetMesh())
							{
								// 소켓 이름 설정 (스켈레탈 메쉬의 소켓 이름)
								FName SocketName = TEXT("PelvisSocket"); // 적절한 소켓 이름으로 변경
								PlayerCharacter->StaticMeshComponent->AttachToComponent(
									PlayerCharacter->GetMesh(),
									FAttachmentTransformRules::SnapToTargetIncludingScale,
									SocketName
								);
							}
						}
					}
				}
			}
		}
	}
}

void UMProjectWidget_Drigger::OnClick_EXIT()
{
	OnClickBackLevel();
}

void UMProjectWidget_Drigger::OnClick_GameClear()
{
	if(W_Ending_BP)
	{
		W_Ending_BP->UpdateDriggerResult();
		W_Ending_BP->Show();
	}
}

void UMProjectWidget_Drigger::Warning_AnimationPlay()
{
	if(Image_Warning && Warning_Animation)
	{
		Image_Warning->SetBrushFromSpriteName("SPR_ToolMiss_Image");
		Image_Warning->SetVisibility(ESlateVisibility::Visible);
	
		PlayAnimation(Warning_Animation,0.0f);
	}
}

void UMProjectWidget_Drigger::Warning_AnimationFinished()
{
	if(Image_Warning)
	{
		Image_Warning->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMProjectWidget_Drigger::TouchText_AnimationPlay()
{
	if(TouchText_Animation)
	{
		PlayAnimation(TouchText_Animation, 0.0f);
	}
}

void UMProjectWidget_Drigger::UpdateDiggerHPLog(int32 NewHP)
{
	UE_LOG(LogTemp, Log, TEXT("UpdateDiggerHPLog called with NewHP: %d"), NewHP);

	switch (NewHP)
	{
	case 2:
		if(Image_Health3)
			Image_Health3->SetBrushFromSpriteName("SPR_Energy0_Image");
		if(g_SoundMgrValid)
		{
			g_SoundMgr->Stop();
			g_SoundMgr->ButtonPlaySound(0.0f, "Sound_RunMiss_Cue");
		}
		Warning_AnimationPlay();
		break;
	case 1:
		if(Image_Health2)
			Image_Health2->SetBrushFromSpriteName("SPR_Energy0_Image");
		if(g_SoundMgrValid)
		{
			g_SoundMgr->Stop();
			g_SoundMgr->ButtonPlaySound(0.0f, "Sound_RunMiss_Cue");
		}
		Warning_AnimationPlay();
		break;
	case 0:
		if(Image_Health1)
			Image_Health1->SetBrushFromSpriteName("SPR_Energy0_Image");
		if(Image_GameClear && Canvas_GameClear&&Button_GameClear)
		{
			Image_GameClear->SetBrushFromSpriteName("SPR_Fail_Image");
			Canvas_GameClear->SetVisibility(ESlateVisibility::Visible);
			Button_GameClear->SetVisibility(ESlateVisibility::Collapsed);
			bIsTimerActive = false;
			if(g_SoundMgrValid)
			{
				g_SoundMgr->Stop();
				g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Fail3_Cue");
			}
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMProjectWidget_Drigger::OnDelayedAnimationPlay, 3.0f, true);

		}
		break;
	default:
		break;
	}
}

void UMProjectWidget_Drigger::UpdateDiggerScoreLog(int32 NewScore)
{
	FString ScoreText = FString::Printf(TEXT("%d M"), NewScore);
	TextBlock_Score->SetText(FText::FromString(ScoreText));
}

void UMProjectWidget_Drigger::OnTimerFinished()
{
	bIsTimerActive = false;
	Seconds = 0;
	Milliseconds = 0;
	
	if(TextBlock_Timer && Canvas_GameClear && Button_GameClear)
	{
		if(g_SoundMgrValid)
		{
			g_SoundMgr->Stop();
			g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Clear_Cue");
		}
		TextBlock_Timer->SetText(FText::FromString("00:00"));
		Canvas_GameClear->SetVisibility(ESlateVisibility::Visible);
		Button_GameClear->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMProjectWidget_Drigger::OnDelayedAnimationPlay, 3.0f, true);

	UE_LOG(LogTemp, Log, TEXT("Timer finished!"));
}

void UMProjectWidget_Drigger::OnDelayedAnimationPlay()
{
	if(Button_GameClear)
	Button_GameClear->SetVisibility(ESlateVisibility::Visible);
	TouchText_AnimationPlay();
}

void UMProjectWidget_Drigger::OnClickBackLevel()
{
	if(g_SoundMgrValid)
	{
		g_SoundMgr->Stop();
		g_SoundMgr->ButtonPlaySound(0.0f, "Sound_Button_Cue");
	}
	
	UGameplayStatics::OpenLevel(GetWorld(),"Level_MProject");
}