// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSLevelManageTypeRecordMgr.h"
#include "Misc/Paths.h"


CSLevelManageTypeMgr::CSLevelManageTypeMgr()
	: CSBaseRecordMgr<CSLevelManageTypeMgr, CSLevelManageTypeRecord>()
{

}

CSLevelManageTypeMgr::~CSLevelManageTypeMgr()
{

}

void CSLevelManageTypeMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/LevelManageType.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSLevelManageTypeMgr::Release()
{
	CSBaseRecordMgr::Release();

}

void CSLevelManageTypeMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSLevelManageTypeRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);

}