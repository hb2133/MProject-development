// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSModelResourceRecordMgr.h"
#include "Misc/Paths.h"


CSModelResourceRecordMgr::CSModelResourceRecordMgr()
	: CSBaseRecordMgr<CSModelResourceRecordMgr, CSModelResourceRecord>()
{

}

CSModelResourceRecordMgr::~CSModelResourceRecordMgr()
{

}

void CSModelResourceRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Resource/ModelResource.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSModelResourceRecordMgr::Release()
{
	CSBaseRecordMgr::Release();

}

void CSModelResourceRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSModelResourceRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);

}