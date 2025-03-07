#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h" 
#include "TableLibrary/DataTable/DataRecord/CSMiniMapRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class CSCORELIBRARY_API CSMiniMapRecordMgr : public CSBaseRecordMgr<CSMiniMapRecordMgr, CSMiniMapRecord>
{
public:
	CSMiniMapRecordMgr();
	~CSMiniMapRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSMiniMapRecord* _pRecord) override;
};

#define g_MiniMapRecordMgr ( CSMiniMapRecordMgr::GetInstance() )