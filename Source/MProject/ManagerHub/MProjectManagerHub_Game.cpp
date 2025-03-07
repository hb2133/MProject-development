// Fill out your copyright notice in the Description page of Project Settings.

#include "MProjectManagerHub_Game.h"
#include "CoreLibrary/Manager/CSSoundMgr.h"
#include "MProject/Manager/MPAdMobMgr.h"
#include "MProject/Manager/MPCustomizeMgr.h"

#include "MProject/Manager/MProjectMgr.h"

#include "TableLibrary/Manager/CSTableMgr.h"
#include "UILibrary/Manager/CSGameMsgMgr.h"
#include "UILibrary/Manager/CSUIMgr.h"


using namespace ManagerHub;
using namespace ManagerHub::Game;

void MProjectManagerHub_Game::InitManagers()
{
	//:: Global
	Init(EManageState::eGlobalInit, EGameManagerID::eUIMgr, g_UIMgr);
	Init(EManageState::eGlobalInit,EGameManagerID::eTableMgr,g_TableMgr);
	Init(EManageState::eGlobalInit,EGameManagerID::eSoundMgr,g_SoundMgr);
	Init(EManageState::eGlobalInit,EGameManagerID::eGameMsgMgr,g_GameMsgMgr);
	Init(EManageState::ePlayInit,EGameManagerID::eMProjectMgr,g_MProjectMgr);
	Init(EManageState::eGlobalInit,EGameManagerID::eMPCustomizeMgr,g_MPCustomizeMgr);
	Init(EManageState::eGlobalInit,EGameManagerID::eMPAdMobMgr,g_MPAdMobMgr);
}