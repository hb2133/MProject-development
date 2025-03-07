// Fill out your copyright notice in the Description page of Project Settings.

#include "CSCSVParser.h"

#include "Misc/FileHelper.h"
#include "Misc/CString.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "HAL/FileManager.h"

#include "Serialization/Csv/CsvParser.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonSerializer.h"
#include "JsonReader.h"

bool CSCSVParser::ReadCSVFile(const FString& _strfilePath)
{
	//:: Load Table
	FString _TextData;
	FString _Path = _strfilePath;

	//:: Use LoadFileToStringArray
	//:: (FString 기반으로 작업, 쉼표로 컬럼구분. Json 사용시 컬럼구분 쉼표와 겹쳐서 이슈 발생)
	//TArray<FString> _arrTextData;
	//if(FFileHelper::LoadFileToStringArray(_arrTextData, *_Path))
	//{
	//	m_rRows.Empty();

	//	//:: Parse CSV Data
	//	for (auto iter : _arrTextData)
	//	{
	//		TArray<FString> _ColumnData;
	//		iter.ParseIntoArray(_ColumnData, TEXT(","), false);

	//		m_rRows.Add(_ColumnData);
	//		//UE_LOG(LogTemp, Log, TEXT("Parse CSV Data - %s"), *iter);
	//	}

	//	//:: Parse Column Name
	//	if (m_rRows.IsValidIndex(COLUMNNAMEROW_IDX))
	//	{
	//		for (auto iter : m_rRows[COLUMNNAMEROW_IDX])
	//			m_rColNameRow.Add(iter);
	//	}
	//	return true;
	//}

	//:: Use FCsvParser : Json 데이터 사용을 위해서 개선
	//:: (const TCHAR 기반이므로 FString 변환시 잘못 참조하면 Development 패키징에서 크래시 위험이 있어 주의할 것)
	if (FFileHelper::LoadFileToString(_TextData, *_Path))
	{
		m_rRows.Empty();
		
		//:: Parse CSV Data
		FCsvParser* _pCsvParser = new FCsvParser(_TextData);
		if (_pCsvParser)
		{
			const FCsvParser::FRows& _rRow = _pCsvParser->GetRows();

			for(int i = 0; i < _rRow.Num(); ++i)
			{
				TArray<const TCHAR*>* _Row = const_cast<TArray<const TCHAR*>*>(&_rRow[i]);
				TArray<FString> _ColumnData;

				for (auto& ColumnIter : *_Row)
					_ColumnData.Add(const_cast<TCHAR*>(ColumnIter));
				
				m_rRows.Add(_ColumnData);
			}
			
			delete _pCsvParser;
         	_pCsvParser = nullptr;
		}

		//:: Parse Column Name
		if (m_rRows.IsValidIndex(COLUMNNAMEROW_IDX))
		{
			for (auto iter : m_rRows[COLUMNNAMEROW_IDX])
				m_rColNameRow.Add(iter);
		}
		return true;
	}
	return false;
}

bool CSCSVParser::GetRowTid(const int& _nRowIdx, FString& _OutTid)
{
	if (m_rRows.IsValidIndex(_nRowIdx))
	{
		if (m_rRows[_nRowIdx].IsValidIndex(TABLEKEY_IDX))
		{
			_OutTid = m_rRows[_nRowIdx][TABLEKEY_IDX];
			return true;
		}
	}
	return false;
}

bool CSCSVParser::GetRowColName(const int& _nColIdx, FString& _OutName)
{
	if (m_rColNameRow.IsValidIndex(_nColIdx))
	{
		_OutName = m_rColNameRow[_nColIdx];
		return true;
	}
	return false;
}

int CSCSVParser::GetRowCount()
{
	return m_rRows.Num();
}

int CSCSVParser::GetColumnCount()
{
	return m_rColNameRow.Num();
}


bool CSCSVParser::TryGetValue(const FString& _Name, const int& _nRowIdx, FString& OutValue)
{
	OutValue = this->GetValue(_Name, _nRowIdx);
	return OutValue.Len() ? true : false;
}

bool CSCSVParser::TryGetValue_Name(const FString& _Name, const int& _nRowIdx, FName& OutValue)
{
	OutValue = *this->GetValue(_Name, _nRowIdx);
	return OutValue.GetStringLength() ? true : false;
}

bool CSCSVParser::TryGetValue_float(const FString& _Name, const int& _nRowIdx, float& OutValue)
{
	FString _strValue = this->GetValue(_Name, _nRowIdx);
	OutValue = FCString::Atof(*_strValue);

	if (OutValue == 0.f)
		return _strValue.Equals(FString("0"));

	return _strValue.Len() ? true : false;
}

bool CSCSVParser::TryGetValue_int(const FString& _Name, const int& _nRowIdx, int& OutValue)
{
	FString _strValue = this->GetValue(_Name, _nRowIdx);
	OutValue = FCString::Atoi(*_strValue);

	if (OutValue == 0)
		return _strValue.Equals(FString("0"));

	return _strValue.Len() ? true : false;
}

bool CSCSVParser::TryGetValue_bool(const FString& _Name, const int& _nRowIdx, bool& OutValue)
{
	FString _strValue = this->GetValue(_Name, _nRowIdx);
	if (_strValue.Len())
	{
		OutValue = _strValue.ToBool();
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonArray(const FString& _Name, const int& _nRowIdx, TArray<FString>& OutArray)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);
	if(ParseJsonData.Num() > 0)
	{
		for (auto& iter : ParseJsonData)
			OutArray.Add(iter->AsString());
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonArrayName(const FString& _Name, const int& _nRowIdx, TArray<FName>& OutArray)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);
	if (ParseJsonData.Num() > 0)
	{
		for (auto& iter : ParseJsonData)
			OutArray.Add(*iter->AsString());
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonArrayFloat(const FString& _Name, const int& _nRowIdx, TArray<float>& OutArray)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);
	if (ParseJsonData.Num() > 0)
	{
		for (auto& iter : ParseJsonData)
			OutArray.Add(static_cast<float>(iter->AsNumber()));
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonArrayInt(const FString& _Name, const int& _nRowIdx, TArray<int>& OutArray)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);
	if (ParseJsonData.Num() > 0)
	{
		for (auto& iter : ParseJsonData)
			OutArray.Add(static_cast<int>(iter->AsNumber()));
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonArrayBool(const FString& _Name, const int& _nRowIdx, TArray<bool>& OutArray)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);
	if (ParseJsonData.Num() > 0)
	{
		for (auto& iter : ParseJsonData)
			OutArray.Add(iter->AsString().ToBool());
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonVector(const FString& _Name, const int& _nRowIdx, FVector& OutVector)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);
	
	if (ParseJsonData.Num() == VECTOR_DATA_SIZE)
	{
		OutVector.X = static_cast<float>(ParseJsonData[VECTOR_IDX_X]->AsNumber());
		OutVector.Y = static_cast<float>(ParseJsonData[VECTOR_IDX_Y]->AsNumber());
		OutVector.Z = static_cast<float>(ParseJsonData[VECTOR_IDX_Z]->AsNumber());
		return true;
	}
	return false;
}

bool CSCSVParser::TryGetValue_JsonRotator(const FString& _Name, const int& _nRowIdx, FRotator& OutRotator)
{
	TArray<TSharedPtr<FJsonValue>> ParseJsonData = this->GetJsonValue(_Name, _nRowIdx);

	if (ParseJsonData.Num() == ROTATOR_DATA_SIZE)
	{
		OutRotator.Pitch = static_cast<float>(ParseJsonData[ROTATOR_IDX_PITCH]->AsNumber());
		OutRotator.Yaw = static_cast<float>(ParseJsonData[ROTATOR_IDX_YAW]->AsNumber());
		OutRotator.Roll = static_cast<float>(ParseJsonData[ROTATOR_IDX_ROLL]->AsNumber());
		return true;
	}
	return false;
}

FString CSCSVParser::GetValue(const FString& _Name, const int& _nRowIdx)
{
	int _nColumnIdx = m_rColNameRow.IndexOfByKey(_Name);

	if (m_rRows.IsValidIndex(_nRowIdx))
	{
		if (m_rRows[_nRowIdx].IsValidIndex(_nColumnIdx))
			return m_rRows[_nRowIdx][_nColumnIdx];
	}
	return FString("");
}

TArray<TSharedPtr<FJsonValue>> CSCSVParser::GetJsonValue(const FString& _Name, const int& _nRowIdx)
{
	FString _strValue = this->GetValue(_Name, _nRowIdx);
	TArray<TSharedPtr<FJsonValue>> ParseJsonData;

	if (_strValue.Len())
	{
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(_strValue);
		FJsonSerializer::Deserialize(JsonReader, ParseJsonData);
	}
	return ParseJsonData;
}
