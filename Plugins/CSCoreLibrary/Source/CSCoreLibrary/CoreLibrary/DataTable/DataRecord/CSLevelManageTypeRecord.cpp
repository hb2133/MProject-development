// Fill out your copyright notice in the Description page of Project Settings.

#include "CSLevelManageTypeRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSLevelManageTypeRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	FString _strManageType;
	_Parser.TryGetValue(FString("manage_type"), nRowIdx, _strManageType);
	m_eManageType = ManagerHub::EManageState::GetEnum(_strManageType, false);

	_Parser.TryGetValue_Name(FString("first_widget"), nRowIdx, m_strFirstWidget);
	_Parser.TryGetValue_Name(FString("default_BGM"), nRowIdx, m_strDefaultBGM);
}
