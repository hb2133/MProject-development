// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSSpriteResourceRecordMgr.h"
#include "Misc/Paths.h"


CSSpriteResourceRecordMgr::CSSpriteResourceRecordMgr()
	: CSBaseRecordMgr<CSSpriteResourceRecordMgr, CSSpriteResourceRecord>()
{

}

CSSpriteResourceRecordMgr::~CSSpriteResourceRecordMgr()
{

}

void CSSpriteResourceRecordMgr::Load()
{
	CSBaseRecordMgr::Load();

	FString _strPath = FString::Printf(TEXT("%sTextData/csv/Resource/SpriteResource.csv"), *FPaths::ProjectContentDir());
	LoadFromCSVTable(_strPath);
}

void CSSpriteResourceRecordMgr::Release()
{
	CSBaseRecordMgr::Release();

}

void CSSpriteResourceRecordMgr::AddRecord(const FString& _strTid, const int& _nRowIdx, CSSpriteResourceRecord* _pRecord)
{
	CSBaseRecordMgr::AddRecord(_strTid, _nRowIdx, _pRecord);

}