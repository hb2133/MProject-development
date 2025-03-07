#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h" 
#include "TableLibrary//DataTable/DataRecord/CSSkyRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class CSCORELIBRARY_API CSSkyRecordMgr : public CSBaseRecordMgr<CSSkyRecordMgr, CSSkyRecord>
{
public:
	CSSkyRecordMgr();
	~CSSkyRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSSkyRecord* _pRecord) override;
};

#define g_SkyRecordMgr ( CSSkyRecordMgr::GetInstance() )