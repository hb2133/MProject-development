// Fill out your copyright notice in the Description page of Project Settings.

#include "CSBaseRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSBaseRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	m_strTid = *strTid;
}

