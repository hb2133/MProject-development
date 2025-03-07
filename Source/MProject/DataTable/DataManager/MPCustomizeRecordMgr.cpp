#include "MPCustomizeRecordMgr.h"

MPCustomizeRecordMgr::MPCustomizeRecordMgr()
	:CSBaseRecordMgr<MPCustomizeRecordMgr, MPCustomizeRecord>()
{
}

MPCustomizeRecordMgr::~MPCustomizeRecordMgr()
{
}

void MPCustomizeRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/MPCustomizeItem.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void MPCustomizeRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void MPCustomizeRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, MPCustomizeRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}
