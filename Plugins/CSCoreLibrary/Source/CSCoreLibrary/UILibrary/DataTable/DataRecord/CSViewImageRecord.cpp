// Fill out your copyright notice in the Description page of Project Settings.

#include "CSViewImageRecord.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSViewImageRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue_Name(FString("ImageName"), nRowIdx, _strImageName);
	_Parser.TryGetValue_Name(FString("ImagePath"), nRowIdx, _strImagePath);
}
