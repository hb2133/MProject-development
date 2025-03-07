// Fill out your copyright notice in the Description page of Project Settings.

#include "CSSoundResourceRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSSoundResourceRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseResourceRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue("AssetFileName",nRowIdx,m_strSoundName);
}
