#pragma once
#include "ResourceLibrary/DataTable/DataRecord/CSMaterialInstanceRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class CSCORELIBRARY_API CSMaterialInstanceRecordMgr : public CSBaseRecordMgr<CSMaterialInstanceRecordMgr,CSMaterialInstanceRecord>
{
public:
	CSMaterialInstanceRecordMgr();
	~CSMaterialInstanceRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSMaterialInstanceRecord* _pRecord) override;

};
#define g_MaterialInstanceResourceMgr ( CSMaterialInstanceRecordMgr::GetInstance() )