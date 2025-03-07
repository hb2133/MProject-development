#include "MPCustomizeSpriteRecordMgr.h"

MPCustomizeSpriteRecordMgr::MPCustomizeSpriteRecordMgr()
	:CSBaseRecordMgr<MPCustomizeSpriteRecordMgr, MPCustomizeSpriteRecord>()
{
}

MPCustomizeSpriteRecordMgr::~MPCustomizeSpriteRecordMgr()
{
}

void MPCustomizeSpriteRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/MPCustomizeSprite.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void MPCustomizeSpriteRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void MPCustomizeSpriteRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, MPCustomizeSpriteRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}

FString MPCustomizeSpriteRecordMgr::GetSpriteName(const FString& _strTid)
{
	FString strValue = FString("");
	if(MPCustomizeSpriteRecord* pRecord = MPCustomizeSpriteRecordMgr::GetInstance()->FindRecord(_strTid))
	{
		strValue = pRecord->m_strSpriteName;
	}
	return  strValue;
}
