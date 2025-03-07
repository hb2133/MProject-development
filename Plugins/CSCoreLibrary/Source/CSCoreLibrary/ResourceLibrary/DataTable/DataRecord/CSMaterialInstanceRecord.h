#pragma once
#include "CSBaseResourceRecord.h"

class CSCORELIBRARY_API CSMaterialInstanceRecord : public CSBaseResourceRecord
{
public:
	
public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
