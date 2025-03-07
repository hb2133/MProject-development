#include "MCStringTableDataRecordMgr.h"

MCStringTableDataRecordMgr::MCStringTableDataRecordMgr()
:CSBaseRecordMgr<MCStringTableDataRecordMgr, MCStringTableDetailRecord>()
{
}

MCStringTableDataRecordMgr::~MCStringTableDataRecordMgr()
{
}

void MCStringTableDataRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Define_String_Local.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);


}

void MCStringTableDataRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void MCStringTableDataRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, MCStringTableDetailRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}