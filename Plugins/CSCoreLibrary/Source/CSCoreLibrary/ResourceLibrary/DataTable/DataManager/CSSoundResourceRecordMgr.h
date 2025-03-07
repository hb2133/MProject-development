// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "ResourceLibrary/DataTable/DataRecord/CSSoundResourceRecord.h"

class CSCORELIBRARY_API CSSoundResourceRecordMgr : public CSBaseRecordMgr<CSSoundResourceRecordMgr, CSSoundResourceRecord>
{
public:
	CSSoundResourceRecordMgr();
	~CSSoundResourceRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSSoundResourceRecord* _pRecord) override;
	FString GetAssetNameByTid(const FString& strTid);

};

#define g_SoundResourceMgr ( CSSoundResourceRecordMgr::GetInstance() )
