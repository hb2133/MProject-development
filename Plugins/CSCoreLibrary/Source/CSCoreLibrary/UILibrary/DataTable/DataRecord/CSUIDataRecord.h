// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class CSCORELIBRARY_API CSUIDataRecord : public CSBaseRecord
{
public:
	FName _strUIBPName;
	FName _strUIPath;
	FName _strBackBtnActionType;

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
