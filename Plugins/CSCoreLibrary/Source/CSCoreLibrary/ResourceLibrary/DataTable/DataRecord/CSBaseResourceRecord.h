// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"

class CSCORELIBRARY_API CSBaseResourceRecord : public CSBaseRecord
{
public:
	FName _strAssetFileName = FName("");
	nAssetType::en _eAssetType = nAssetType::Max;

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
