// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSDefineRecordMgr.h"
#include "Misc/Paths.h"

CSDefineRecordMgr::CSDefineRecordMgr()
	: CSBaseRecordMgr<CSDefineRecordMgr, CSDefineRecord>()
{
	
}

CSDefineRecordMgr::~CSDefineRecordMgr()
{
}

void CSDefineRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Define_String.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath, 0);

	_strPath = FString::Printf(TEXT("%sTextData/csv/Define_Number.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath, 1);
}

void CSDefineRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSDefineRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSDefineRecord* _pRecord)
{	
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}

FString CSDefineRecordMgr::GetValue_String(const FString& _strTid)
{
	FString strValue = FString("");
	if(CSDefineRecord* pRecord = CSDefineRecordMgr::GetInstance()->FindRecord(_strTid))
	{
		if(pRecord->m_ValueType.Equals(FString("string")))
			strValue = pRecord->m_Value;
	}
	return  strValue;
}

float CSDefineRecordMgr::GetValue_Number(const FString& _strTid)
{
	float value = 0.f;
	if(CSDefineRecord* pRecord = CSDefineRecordMgr::GetInstance()->FindRecord(_strTid,1))
	{
		if(pRecord->m_ValueType.Equals(FString("number")))
			value = FCString::Atof(*pRecord->m_Value);
	}
	return value;
}
