#include "CSMiniMapRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"
void CSMiniMapRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);
	
	_Parser.TryGetValue_float(FString("StartPositionX"), nRowIdx, m_fStartPositionX);
	_Parser.TryGetValue_float(FString("StartPositionY"), nRowIdx, m_fStartPositionY);
	_Parser.TryGetValue_float(FString("XPercent"), nRowIdx, m_XPercent);
	_Parser.TryGetValue_float(FString("Ypercent"), nRowIdx, m_YPercent);
	_Parser.TryGetValue_float(FString("UMGX"), nRowIdx, m_fUMGX);
	_Parser.TryGetValue_float(FString("UMGY"), nRowIdx, m_fUMGY);
	_Parser.TryGetValue_float(FString("PlayerIconX"), nRowIdx, m_fPlayerIconX);
	_Parser.TryGetValue_float(FString("PlayerIconY"), nRowIdx, m_fPlayerIconY);
	_Parser.TryGetValue(FString("Image"), nRowIdx, m_strImageName);
	_Parser.TryGetValue_float(FString("IconAngle"), nRowIdx, m_fPlayerIconAngle);
	_Parser.TryGetValue_bool(FString("PathEnable"),nRowIdx,m_bPathEnable);
}
