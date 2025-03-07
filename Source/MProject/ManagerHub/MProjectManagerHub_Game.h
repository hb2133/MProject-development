// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/ManagerHub/CSManagerHub.h"
#include "CoreLibrary/Manager/CSBaseManager.h"

namespace ManagerHub
{
	namespace Game
	{
		enum class EGameManagerID : int
		{
			eNone = -1,

			//:: Global
			eUIMgr,
			eSoundMgr,
			eTableMgr,
			eGameMsgMgr,			
			eMProjectMgr,
			eMPCustomizeMgr,
			eMPAdMobMgr,
			Max
		};
	}
}

class MPROJECT_API MProjectManagerHub_Game : public CSManagerHub<MProjectManagerHub_Game, UCSBaseManager, ManagerHub::Game::EGameManagerID>
{
public:
	MProjectManagerHub_Game() {}
	~MProjectManagerHub_Game() {}

public:
	virtual void InitManagers();
};

#define g_ManagerHub_Game ( MProjectManagerHub_Game::GetInstance() )