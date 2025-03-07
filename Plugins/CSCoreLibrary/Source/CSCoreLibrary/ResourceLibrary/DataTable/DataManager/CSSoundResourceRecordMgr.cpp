// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSSoundResourceRecordMgr.h"
#include "Misc/Paths.h"


CSSoundResourceRecordMgr::CSSoundResourceRecordMgr()
	: CSBaseRecordMgr<CSSoundResourceRecordMgr, CSSoundResourceRecord>()
{

}

CSSoundResourceRecordMgr::~CSSoundResourceRecordMgr()
{

}

void CSSoundResourceRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Resource/SoundResource.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSSoundResourceRecordMgr::Release()
{
	CSBaseRecordMgr::Release();

}

void CSSoundResourceRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSSoundResourceRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);

}

FString CSSoundResourceRecordMgr::GetAssetNameByTid(const FString& strTid)
{
	FString strAssetName = "";
	if(CSSoundResourceRecord* pRecord = this->FindRecord(strTid))
	{
		strAssetName = pRecord->m_strSoundName;
	}
	return strAssetName;
}
