// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h" 

#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "UILibrary/DataTable/DataRecord/CSUIDataRecord.h"

class CSCORELIBRARY_API CSUIDataRecordMgr : public CSBaseRecordMgr<CSUIDataRecordMgr, CSUIDataRecord>
{
public:
	CSUIDataRecordMgr();
	~CSUIDataRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSUIDataRecord* _pRecord) override;
};

#define g_UIDataRecordMgr ( CSUIDataRecordMgr::GetInstance() )
