// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

typedef TSharedPtr<CSBaseRecord> CSBaseRecordPtr;

typedef TMap<FString /*TID*/, CSBaseRecordPtr> TIDRecords;
typedef TArray<FString /*TID*/> TIDKeys;

class CSDataTable
{
public:
	void ReleaseTable()
	{
		m_RowRecords.Empty();
	}

	/*
	template <typename TRecord>
	void ReadBin(const FString& filePath)
	{
	}
	*/

public: //:: Row Record Data
	TIDRecords m_RowRecords;
	TIDKeys m_Keys;
};
