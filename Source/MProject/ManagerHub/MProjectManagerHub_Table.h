// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/ManagerHub/CSManagerHub.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

namespace ManagerHub
{
	namespace Table
	{
		enum class ETBManagerID : int
		{
			eNone = -1,
			eActorDataRecordMgr,
			eUIDataRecordMgr,
			eDefineRecordMgr,
			eLevelDetailDataRecordMgr,
			ePopupRecordMgr,
			eStringTableRecordMgr,
			eMPCustomizeRecordMgr,
			eMPSpriteRecordMgr,
			Max		
		};
	}
}

class MPROJECT_API MProjectManagerHub_Table : public CSManagerHub<MProjectManagerHub_Table, CSRecordMgrInterface, ManagerHub::Table::ETBManagerID>
{
public:
	MProjectManagerHub_Table() {}
	~MProjectManagerHub_Table() {}

public:
	virtual void InitManagers();
};

#define g_ManagerHub_Table ( MProjectManagerHub_Table::GetInstance() )