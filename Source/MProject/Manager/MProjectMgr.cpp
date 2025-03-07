// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectMgr.h"

#include "Kismet/GameplayStatics.h"
#include "MProject/PlayerCharacter/MProject_Character.h"
#include "MProject/PlayerCharacter/MProject_Chawracter_Drigger.h"

void UMProjectMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMProjectMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UMProjectMgr::Load()
{
	Super::Load();

}

void UMProjectMgr::Release()
{
	Super::Release();
}

void UMProjectMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void UMProjectMgr::StartPlayRun()
{
}

void UMProjectMgr::StartPlayDigging()
{
}

void UMProjectMgr::CreateRunningScore()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Character* PlayerCharacter = Cast<AMProject_Character>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			int32 WarningCount = PlayerCharacter->GetWarningCount();
			SetScore((60 - GetCurrentTime()) * 150 - (WarningCount * 100) + 540);
			UE_LOG(LogTemp, Log, TEXT("달리기 점수: %f"), g_MProjectMgr->GetScore());
		}
	}
}

void UMProjectMgr::CreateDriggerScore()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			int32 WarningCount = PlayerCharacter->GetWarningCount();
			SetScore(GetDriggerScore() * 10 * 3 - WarningCount * 5);
			UE_LOG(LogTemp, Log, TEXT("삽질하기 점수: %f"), g_MProjectMgr->GetScore());
		}
	}
}

void UMProjectMgr::SetScore(float score)
{
	if(score < 0)
	{
		m_fScore = 0;
	}
	else
	{
		m_fScore = score;
	}
}