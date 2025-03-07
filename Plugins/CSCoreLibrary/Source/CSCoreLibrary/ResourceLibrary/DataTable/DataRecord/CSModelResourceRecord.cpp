// Fill out your copyright notice in the Description page of Project Settings.

#include "CSModelResourceRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSModelResourceRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseResourceRecord::ReadCSVData(strTid, nRowIdx, _Parser);

}
