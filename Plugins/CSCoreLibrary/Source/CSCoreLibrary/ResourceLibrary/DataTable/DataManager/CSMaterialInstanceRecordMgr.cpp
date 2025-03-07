#include "CSMaterialInstanceRecordMgr.h"

CSMaterialInstanceRecordMgr::CSMaterialInstanceRecordMgr()
{
}

CSMaterialInstanceRecordMgr::~CSMaterialInstanceRecordMgr()
{
}

void CSMaterialInstanceRecordMgr::Load()
{
	CSBaseRecordMgr<CSMaterialInstanceRecordMgr, CSMaterialInstanceRecord>::Load();
	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Resource/MaterialInstanceResource.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSMaterialInstanceRecordMgr::Release()
{
	CSBaseRecordMgr<CSMaterialInstanceRecordMgr, CSMaterialInstanceRecord>::Release();
}

void CSMaterialInstanceRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx,
	CSMaterialInstanceRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}
