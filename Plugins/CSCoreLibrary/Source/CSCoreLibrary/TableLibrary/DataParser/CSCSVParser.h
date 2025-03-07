// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"

#define COLUMNNAMEROW_IDX 0
#define TABLEKEY_IDX 0

#define VECTOR_DATA_SIZE 3
#define ROTATOR_DATA_SIZE 3

#define VECTOR_IDX_X 0
#define VECTOR_IDX_Y 1
#define VECTOR_IDX_Z 2

#define ROTATOR_IDX_PITCH 0
#define ROTATOR_IDX_YAW 1
#define ROTATOR_IDX_ROLL 2

class CSCORELIBRARY_API CSCSVParser
{
	typedef TArray<TArray<FString>> FCSVRows;

public:
	bool ReadCSVFile(const FString& _strfilePath);
	int GetRowCount();
	int GetColumnCount();
	bool GetRowTid(const int& _nRowIdx, FString& _OutTid);
	bool GetRowColName(const int& _nColIdx, FString& _OutName);

public:
	bool TryGetValue(const FString& _Name, const int& _nRowIdx, FString& OutValue);
	bool TryGetValue_Name(const FString& _Name, const int& _nRowIdx, FName& OutValue);
	bool TryGetValue_float(const FString& _Name, const int& _nRowIdx, float& OutValue);
	bool TryGetValue_int(const FString& _Name, const int& _nRowIdx, int& OutValue);
	bool TryGetValue_bool(const FString& _Name, const int& _nRowIdx, bool& OutValue);

public:
	bool TryGetValue_JsonArray(const FString& _Name, const int& _nRowIdx, TArray<FString>& OutArray);
	bool TryGetValue_JsonArrayName(const FString& _Name, const int& _nRowIdx, TArray<FName>& OutArray);
	bool TryGetValue_JsonArrayFloat(const FString& _Name, const int& _nRowIdx, TArray<float>& OutArray);
	bool TryGetValue_JsonArrayInt(const FString& _Name, const int& _nRowIdx, TArray<int>& OutArray);
	bool TryGetValue_JsonArrayBool(const FString& _Name, const int& _nRowIdx, TArray<bool>& OutArray);

public:
	bool TryGetValue_JsonVector(const FString& _Name, const int& _nRowIdx, FVector& OutVector);
	bool TryGetValue_JsonRotator(const FString& _Name, const int& _nRowIdx, FRotator& OutRotator);

private:
	FString GetValue(const FString& _Name, const int& _nRowIdx);
	TArray<TSharedPtr<FJsonValue>> GetJsonValue(const FString& _Name, const int& _nRowIdx);

private:
	CSCSVParser::FCSVRows m_rRows;
	TArray<FString> m_rColNameRow;
};
