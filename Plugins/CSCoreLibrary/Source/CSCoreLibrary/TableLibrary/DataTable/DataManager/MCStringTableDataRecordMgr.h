#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h" 
#include "TableLibrary/DataTable/DataRecord/MCStringTableDetailRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class CSCORELIBRARY_API MCStringTableDataRecordMgr : public CSBaseRecordMgr<MCStringTableDataRecordMgr, MCStringTableDetailRecord>
{
public:
	MCStringTableDataRecordMgr();
	~MCStringTableDataRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, MCStringTableDetailRecord* _pRecord) override;

	
};

#define g_StringTableDataRecordMgr ( MCStringTableDataRecordMgr::GetInstance() )