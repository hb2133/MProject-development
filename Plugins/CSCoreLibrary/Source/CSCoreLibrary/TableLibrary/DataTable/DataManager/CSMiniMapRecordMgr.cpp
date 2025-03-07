

#include "CSMiniMapRecordMgr.h"
#include "Misc/Paths.h"


CSMiniMapRecordMgr::CSMiniMapRecordMgr()
	:CSBaseRecordMgr<CSMiniMapRecordMgr, CSMiniMapRecord>()
{
}

CSMiniMapRecordMgr::~CSMiniMapRecordMgr()
{
}

void CSMiniMapRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/MiniMapRecord.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath,0);


}

void CSMiniMapRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSMiniMapRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSMiniMapRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}