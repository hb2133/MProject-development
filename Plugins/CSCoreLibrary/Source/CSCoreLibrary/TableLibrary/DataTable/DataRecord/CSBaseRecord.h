// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class CSCSVParser;

class CSCORELIBRARY_API CSBaseRecord
{
public:
	FName m_strTid;

public:
	virtual ~CSBaseRecord() {}
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
