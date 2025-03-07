// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class CSCORELIBRARY_API CSViewImageRecord : public CSBaseRecord
{
public:
	FName _strImageName;
	FName _strImagePath;

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
