// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceLibrary/DataTable/DataRecord/CSBaseResourceRecord.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"

class CSCORELIBRARY_API CSModelResourceRecord : public CSBaseResourceRecord
{
public:

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
