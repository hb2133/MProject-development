// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "ResourceLibrary/DataTable/DataRecord/CSModelResourceRecord.h"

class CSCORELIBRARY_API CSModelResourceRecordMgr : public CSBaseRecordMgr<CSModelResourceRecordMgr, CSModelResourceRecord>
{
public:
	CSModelResourceRecordMgr();
	~CSModelResourceRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSModelResourceRecord* _pRecord) override;

};

#define g_ModelResourceMgr ( CSModelResourceRecordMgr::GetInstance() )
