// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSActorRecordMgr.h"
#include "Misc/Paths.h"

CSActorRecordMgr::CSActorRecordMgr()
	: CSBaseRecordMgr<CSActorRecordMgr, CSActorRecord>()
{

}

CSActorRecordMgr::~CSActorRecordMgr()
{
}

void CSActorRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/ActorData.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSActorRecordMgr::Release()
{
	CSBaseRecordMgr::Release();
}

void CSActorRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSActorRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);
}