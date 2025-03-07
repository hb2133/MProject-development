// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectInstance.h"

#include "ActorLibrary/Actor/Builder/CSSoundBuilder.h"
#include "CoreLibrary/DataTable/DataManager/CSLevelManageTypeRecordMgr.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "MProject/ManagerHub/MProjectManagerHub_Game.h"
#include "MProject/ManagerHub/MProjectManagerHub_Table.h"
#include "TableLibrary/DataTable/DataManager/CSFunctionPropertyRecordMgr.h"

class UCSGameGlobal;

void UMProjectInstance::Init()
{
	Super::Init();
	g_FileMgr->Load();
	g_LevelManageTypeMgr->Load();
	g_FunctionPropertyMgr->Load();
	if (UCSGameGlobal* _pGameGlobal = g_GameGlobal)
	{
		_pGameGlobal->InitHub(g_ManagerHub_Table);
		_pGameGlobal->InitHub(g_ManagerHub_Game);

		_pGameGlobal->InitManagers();
		this->InitGameActorBuilder();
		_pGameGlobal->LoadManager(ManagerHub::EManageState::eGlobalInit);

		
		this->InitLevelManageType();
	}

	
	
	this->InitGameActorBuilder();
}

void UMProjectInstance::OnStart()
{
	Super::OnStart();
}

void UMProjectInstance::Shutdown()
{
	Super::Shutdown();
}

void UMProjectInstance::FinishDestroy()
{
	g_FileMgr->Release();
	g_LevelManageTypeMgr->Release();
	g_FunctionPropertyMgr->Release();
	
	Super::FinishDestroy();
}

void UMProjectInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	if (NewWorld == nullptr)
		return;

	//:: Manager Hub Load
	if (m_bGameInstInit)
		this->InitLevelManageType();
	
}

void UMProjectInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
}

void UMProjectInstance::InitGameActorBuilder()
{
	Super::InitGameActorBuilder();

	if (g_ActorMgrValid)
	{
		g_ActorMgr->ReserveActorBuilder<CSSoundBuilder>();
	}
}

void UMProjectInstance::InitLevelManageType()
{
	Super::InitLevelManageType();

	if (UCSGameGlobal* _pGameGlobal = g_GameGlobal)
	{
		if (CSLevelManageTypeRecord* _pRecord = g_LevelManageTypeMgr->FindRecord(m_strCurLevelName))
		{
			_pGameGlobal->LoadManager(_pRecord->m_eManageType);
			g_SoundMgr->InitSound(_pRecord->m_strDefaultBGM);
		}
	}
}
