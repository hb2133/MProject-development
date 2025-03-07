// Fill out your copyright notice in the Description page of Project Settings.

#include "CSBaseResourceRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSBaseResourceRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue_Name(FString("AssetFileName"), nRowIdx, _strAssetFileName);

	FString _strAssetType;
	_Parser.TryGetValue(FString("AssetType"), nRowIdx, _strAssetType);
	_eAssetType = nAssetType::GetEnum(_strAssetType, false);
}
