

#include "CSSkyRecordMgr.h"
#include "Misc/Paths.h"


CSSkyRecordMgr::CSSkyRecordMgr()
	:CSBaseRecordMgr<CSSkyRecordMgr, CSSkyRecord>()
{
}

CSSkyRecordMgr::~CSSkyRecordMgr()
{
}

void CSSkyRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/SkyRecord.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath,0);


}

void CSSkyRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSSkyRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSSkyRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}