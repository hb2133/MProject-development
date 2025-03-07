// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "ResourceLibrary/DataTable/DataRecord/CSSpriteResourceRecord.h"

class CSCORELIBRARY_API CSSpriteResourceRecordMgr : public CSBaseRecordMgr<CSSpriteResourceRecordMgr, CSSpriteResourceRecord>
{
public:
	CSSpriteResourceRecordMgr();
	~CSSpriteResourceRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSSpriteResourceRecord* _pRecord) override;

};

#define g_SpriteResourceMgr ( CSSpriteResourceRecordMgr::GetInstance() )
