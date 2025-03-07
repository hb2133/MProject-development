// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"
#include "CSDefineRecord.h"

class CSCORELIBRARY_API CSDefineRecord : public CSBaseRecord
{
public:
	FString m_ValueType;
	FString m_Value;

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
