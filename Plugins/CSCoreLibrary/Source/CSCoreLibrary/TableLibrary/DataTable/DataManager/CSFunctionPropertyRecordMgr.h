#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"
#include "TableLibrary/DataTable/DataRecord/CSFunctionPropertyRecord.h"


class CSCORELIBRARY_API CSFunctionPropertyRecordMgr : public CSBaseRecordMgr<CSFunctionPropertyRecordMgr, CSFunctionPropertyRecord>
{
public:
	CSFunctionPropertyRecordMgr();
	~CSFunctionPropertyRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSFunctionPropertyRecord* _pRecord) override;
public:
	static bool Is(const nFunctionProperty::en& _eFunctionProperty);
	
};

#define g_FunctionPropertyMgr ( CSFunctionPropertyRecordMgr::GetInstance() )