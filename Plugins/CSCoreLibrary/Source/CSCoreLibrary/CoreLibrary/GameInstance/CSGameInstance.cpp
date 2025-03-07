// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreLibrary/GameInstance/CSGameInstance.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"

void UCSGameInstance::Init()
{
	


	this->LoadData();
	//Super::Init 에서 SubSystem 초기화
	Super::Init();
	m_bGameInstInit = true;
}

void UCSGameInstance::Shutdown()
{
	Super::Shutdown();

	this->ReleaseData();
}

void UCSGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	//:: OldWorld 시점 (레벨 이동 직전에 기존 레벨 반환)
	if (OldWorld)
	{
		m_strOldLevelName = OldWorld->GetMapName().Mid(OldWorld->StreamingLevelsPrefix.Len());
	}

	//:: NewWorld 로드되는 시점 (새 레벨로 진입)
	if (NewWorld)
	{
		if (UCSGameGlobal* _pGameGlobal = g_GameGlobal)
			g_GameGlobal->SetCurWorld(NewWorld);

		m_strCurLevelName = NewWorld->GetMapName().Mid(NewWorld->StreamingLevelsPrefix.Len());
	}
}

void UCSGameInstance::LoadData()
{
	if (UCSGameGlobal* _pGameGlobal = g_GameGlobal)
		_pGameGlobal->Load();
}

void UCSGameInstance::ReleaseData()
{
	if (UCSGameGlobal* _pGameGlobal = g_GameGlobal)
		_pGameGlobal->Release();
}