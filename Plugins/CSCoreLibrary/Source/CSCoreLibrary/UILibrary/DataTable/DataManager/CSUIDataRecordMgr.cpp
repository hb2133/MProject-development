// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSUIDataRecordMgr.h"
#include "Misc/Paths.h"
#include "UILibrary/DataTable/DataRecord/CSUIDataRecord.h"

CSUIDataRecordMgr::CSUIDataRecordMgr()
	: CSBaseRecordMgr<CSUIDataRecordMgr, CSUIDataRecord>()
{
}

CSUIDataRecordMgr::~CSUIDataRecordMgr()
{
}

void CSUIDataRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/UIData.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSUIDataRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSUIDataRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSUIDataRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}