// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "CoreLibrary/DataTable/DataRecord/CSLevelManageTypeRecord.h"

class CSCORELIBRARY_API CSLevelManageTypeMgr : public CSBaseRecordMgr<CSLevelManageTypeMgr, CSLevelManageTypeRecord>
{
public:
	CSLevelManageTypeMgr();
	~CSLevelManageTypeMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSLevelManageTypeRecord* _pRecord) override;

};

#define g_LevelManageTypeMgr ( CSLevelManageTypeMgr::GetInstance() )
