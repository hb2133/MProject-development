// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUIDataRecord.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSUIDataRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue_Name(FString("UIBPName"), nRowIdx, _strUIBPName);	
	_Parser.TryGetValue_Name(FString("UIPath"), nRowIdx, _strUIPath);	
	_Parser.TryGetValue_Name(FString("BackBtnActionType"), nRowIdx, _strBackBtnActionType);
}
