// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "ActorLibrary/DataTable/DataRecord/CSActorRecord.h"

class CSCORELIBRARY_API CSActorRecordMgr : public CSBaseRecordMgr<CSActorRecordMgr, CSActorRecord>
{
public:
	CSActorRecordMgr();
	~CSActorRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSActorRecord* _pRecord) override;
};

#define g_ActorRecordMgr ( CSActorRecordMgr::GetInstance() )