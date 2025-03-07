// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "TableLibrary/DataTable/DataRecord/CSDefineRecord.h"


class CSCORELIBRARY_API CSDefineRecordMgr : public CSBaseRecordMgr<CSDefineRecordMgr, CSDefineRecord>
{
public:
	CSDefineRecordMgr();
	~CSDefineRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSDefineRecord* _pRecord) override;
	
	static FString GetValue_String(const FString& _strTid);
	static float GetValue_Number(const FString& _strTid);
	
};

#define g_CSDefineRecordMgr ( CSDefineRecordMgr::GetInstance() )
