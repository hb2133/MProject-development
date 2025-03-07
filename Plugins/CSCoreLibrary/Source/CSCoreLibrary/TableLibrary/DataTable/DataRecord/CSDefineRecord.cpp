// Fill out your copyright notice in the Description page of Project Settings.

#include "CSDefineRecord.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"


void CSDefineRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue(FString("type"), nRowIdx, m_ValueType);	
	_Parser.TryGetValue(FString("value"), nRowIdx, m_Value);
	
}
