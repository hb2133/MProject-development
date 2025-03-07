#pragma once

#include "CoreMinimal.h"
#include "../DataRecord/MPCustomizeRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class MPCustomizeRecordMgr : public CSBaseRecordMgr<MPCustomizeRecordMgr, MPCustomizeRecord>
{
public:
	MPCustomizeRecordMgr();
	~MPCustomizeRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, MPCustomizeRecord* _pRecord) override;
};

#define g_MPCustomizeRecordMgr ( MPCustomizeRecordMgr::GetInstance() )