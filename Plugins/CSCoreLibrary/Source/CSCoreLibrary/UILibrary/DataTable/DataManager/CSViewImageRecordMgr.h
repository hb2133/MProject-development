// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h" 

#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "UILibrary/DataTable/DataRecord/CSViewImageRecord.h"

class CSCORELIBRARY_API CSViewImageRecordMgr : public CSBaseRecordMgr<CSViewImageRecordMgr, CSViewImageRecord>
{
public:
	CSViewImageRecordMgr();
	~CSViewImageRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSViewImageRecord* _pRecord) override;
};

#define g_ViewImageRecordMgr ( CSViewImageRecordMgr::GetInstance() )
