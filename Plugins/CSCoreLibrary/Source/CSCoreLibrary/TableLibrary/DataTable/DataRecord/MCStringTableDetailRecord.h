#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"
#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class CSCORELIBRARY_API MCStringTableDetailRecord : public CSBaseRecord
{
	
public:
	UPROPERTY(meta=(MultiLine = true))
	FString m_strKO;
	UPROPERTY(meta=(MultiLine = true))
	FString m_strEN;
	

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
