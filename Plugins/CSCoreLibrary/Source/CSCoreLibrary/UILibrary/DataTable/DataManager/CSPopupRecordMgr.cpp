

#include "CSPopupRecordMgr.h"



CSPopupRecordMgr::CSPopupRecordMgr()
	:CSBaseRecordMgr<CSPopupRecordMgr, CSPopupRecord>()
{
}

CSPopupRecordMgr::~CSPopupRecordMgr()
{
}

void CSPopupRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/UIPopup.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSPopupRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSPopupRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSPopupRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}