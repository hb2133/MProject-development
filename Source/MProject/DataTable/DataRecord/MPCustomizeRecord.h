#pragma once

#include "CoreMinimal.h"
#include "MProject/Define/MPCustomizeCommon.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class MPCustomizeRecord : public CSBaseRecord
{
public:
	ItemInfo* m_pItemInfo;
	
public:
	~MPCustomizeRecord();
	
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
