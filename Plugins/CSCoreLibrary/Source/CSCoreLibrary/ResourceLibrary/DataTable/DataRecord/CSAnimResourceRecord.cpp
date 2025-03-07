// Fill out your copyright notice in the Description page of Project Settings.

#include "CSAnimResourceRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSAnimResourceRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseResourceRecord::ReadCSVData(strTid, nRowIdx, _Parser);
	_Parser.TryGetValue_bool(FString("EnableStop"),nRowIdx,m_bEnableStop);
	_Parser.TryGetValue_bool(FString("EnablePlayInJump"),nRowIdx,m_bEnablePlayInJump);
}
