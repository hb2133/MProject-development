// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class MPCustomizeSpriteRecord : public CSBaseRecord
{
public:
	FString m_strSpriteName;

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
