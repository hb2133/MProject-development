#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/Define/CSCommon_Sky.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class CSCORELIBRARY_API CSSkyRecord : public CSBaseRecord
{
public:

	FString m_strName;
	float m_fValue;
	FString m_strType;
	FString m_strParentName;
	FString m_strValue;
	FVector m_vecValue;
	FString m_strTextureValue;
	nParameterType::en m_eParameterType;
	TArray<FString> m_arrParentName;
	float m_fMaxValue;
	float m_fMinValue;
	bool m_bRealTime;
	FVector m_vecMaxColor;
	FVector m_vecMinColor;
	

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
