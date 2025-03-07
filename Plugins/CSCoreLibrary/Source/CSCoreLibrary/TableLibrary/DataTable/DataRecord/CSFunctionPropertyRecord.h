#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"
#include "TableLibrary/Define/CSCommon_FunctionProperty.h"

class CSCORELIBRARY_API CSFunctionPropertyRecord : public CSBaseRecord
{
	
public:
	bool m_bEnable;
	
public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);	
};

