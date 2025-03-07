// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceLibrary/DataTable/DataRecord/CSBaseResourceRecord.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"

class CSCORELIBRARY_API CSSoundResourceRecord : public CSBaseResourceRecord
{
public:
	FString m_strSoundName;
public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
