// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSAnimResourceRecordMgr.h"
#include "Misc/Paths.h"

CSAnimResourceRecordMgr::CSAnimResourceRecordMgr()
	: CSBaseRecordMgr<CSAnimResourceRecordMgr, CSAnimResourceRecord>()
{

}

CSAnimResourceRecordMgr::~CSAnimResourceRecordMgr()
{

}

void CSAnimResourceRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Resource/AnimResource.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSAnimResourceRecordMgr::Release()
{
	CSBaseRecordMgr::Release();

}

void CSAnimResourceRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSAnimResourceRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}