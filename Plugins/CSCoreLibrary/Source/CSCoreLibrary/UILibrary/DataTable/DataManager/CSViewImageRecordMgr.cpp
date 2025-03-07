// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSViewImageRecordMgr.h"
#include "Misc/Paths.h"
#include "UILibrary/DataTable/DataRecord/CSViewImageRecord.h"

CSViewImageRecordMgr::CSViewImageRecordMgr()
	: CSBaseRecordMgr<CSViewImageRecordMgr, CSViewImageRecord>()
{

}

CSViewImageRecordMgr::~CSViewImageRecordMgr()
{
}

void CSViewImageRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/ViewImage.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSViewImageRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSViewImageRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSViewImageRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}