// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"
#include "CoreLibrary/ManagerHub/CSManagerHub.h"

class CSCORELIBRARY_API CSLevelManageTypeRecord : public CSBaseRecord
{
public:
	ManagerHub::EManageState::en m_eManageType = ManagerHub::EManageState::Max;
	FName m_strFirstWidget = NAME_None;
	FName m_strDefaultBGM = NAME_None;
	
public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
