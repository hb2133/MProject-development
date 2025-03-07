#pragma once

#include "CSFunctionPropertyRecordMgr.h"
#include "Misc/Paths.h"


CSFunctionPropertyRecordMgr::CSFunctionPropertyRecordMgr()
	:CSBaseRecordMgr<CSFunctionPropertyRecordMgr, CSFunctionPropertyRecord>()
{
}

CSFunctionPropertyRecordMgr::~CSFunctionPropertyRecordMgr()
{
}

void CSFunctionPropertyRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/FunctionProperty.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSFunctionPropertyRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSFunctionPropertyRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSFunctionPropertyRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}

bool CSFunctionPropertyRecordMgr::Is(const nFunctionProperty::en& _eFunctionProperty)
{
	FString strFunctionProperty = nFunctionProperty::GetFStr(_eFunctionProperty,false);
	if(CSFunctionPropertyRecord* pRecord = CSFunctionPropertyRecordMgr::GetInstance()->FindRecord(strFunctionProperty))
	{
		return  pRecord->m_bEnable;
	}

	return false;
	
}
