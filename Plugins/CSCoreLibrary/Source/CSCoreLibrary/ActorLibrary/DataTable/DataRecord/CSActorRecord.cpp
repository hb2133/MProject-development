// Fill out your copyright notice in the Description page of Project Settings.

#include "CSActorRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSActorRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue_Name(FString("SpawnBP"), nRowIdx, _strSpawnBPName);
}
