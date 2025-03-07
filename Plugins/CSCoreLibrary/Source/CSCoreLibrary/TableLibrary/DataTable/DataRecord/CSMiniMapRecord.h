#pragma once

#include "CoreMinimal.h"
#include "CSBaseRecord.h"

class CSCSVParser;

class CSCORELIBRARY_API CSMiniMapRecord : public CSBaseRecord
{
public:
	
	float m_fStartPositionX;
	float m_fStartPositionY;
	float m_XPercent;
	float m_YPercent;
	FString m_strImageName;
	float m_fUMGX;
	float m_fUMGY;
	float m_fPlayerIconX;
	float m_fPlayerIconY;
	float m_fPlayerIconAngle;
	bool m_bPathEnable;
	

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
