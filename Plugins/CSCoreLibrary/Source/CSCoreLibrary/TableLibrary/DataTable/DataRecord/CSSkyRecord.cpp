#include "CSSkyRecord.h"

#include "TableLibrary//Define/CSCommon_Sky.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSSkyRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);


	_Parser.TryGetValue(FString("Name"), nRowIdx, m_strName);
	_Parser.TryGetValue(FString("Type"), nRowIdx, m_strType);
	_Parser.TryGetValue(FString("ParentName"), nRowIdx, m_strParentName);
	_Parser.TryGetValue_bool(FString("RealTime"), nRowIdx, m_bRealTime);
	m_eParameterType = nParameterType::GetEnum(m_strType,false);

	m_strParentName.ParseIntoArray(m_arrParentName,TEXT(","));
	
	switch (m_eParameterType)
	{
	case nParameterType::Scalar:
		{
			_Parser.TryGetValue_float(FString("Value"), nRowIdx, m_fValue);
			if(m_bRealTime)
			{
				_Parser.TryGetValue_float(FString("MaxValue"), nRowIdx, m_fMaxValue);
				_Parser.TryGetValue_float(FString("MinValue"), nRowIdx, m_fMinValue);
			}
		}break;
	case nParameterType::Texture:
		{
			_Parser.TryGetValue(FString("Value"), nRowIdx, m_strTextureValue);
		}break;
	case nParameterType::Vector:
		{
			_Parser.TryGetValue(FString("Value"), nRowIdx, m_strValue);
			TArray<FString> SplitValue;
			m_strValue.ParseIntoArray(SplitValue,TEXT(","));
	
			if(SplitValue.Num() >2)
			{
				m_vecValue = FVector(FCString::Atof(*SplitValue[0].TrimQuotes()),FCString::Atof(*SplitValue[1].TrimQuotes()),FCString::Atof(*SplitValue[2].TrimQuotes()));
			}
			if(m_bRealTime)
			{
				FString strMinColorValue;
				FString strMaxColorValue;
				_Parser.TryGetValue(FString("MaxValue"), nRowIdx, strMaxColorValue);
				_Parser.TryGetValue(FString("MinValue"), nRowIdx, strMinColorValue);
				TArray<FString> SplitColorValue;
				strMinColorValue.ParseIntoArray(SplitColorValue,TEXT(","));
				if(SplitColorValue.Num() >2)
				{
					m_vecMinColor = FVector(FCString::Atof(*SplitColorValue[0].TrimQuotes()),FCString::Atof(*SplitColorValue[1].TrimQuotes()),FCString::Atof(*SplitColorValue[2].TrimQuotes()));
				}

				SplitColorValue.Empty();
				strMaxColorValue.ParseIntoArray(SplitColorValue,TEXT(","));
				if(SplitColorValue.Num() >2)
				{
					m_vecMaxColor = FVector(FCString::Atof(*SplitColorValue[0].TrimQuotes()),FCString::Atof(*SplitColorValue[1].TrimQuotes()),FCString::Atof(*SplitColorValue[2].TrimQuotes()));
				}
			}
		}break;
		default:
			break;
	}




}
