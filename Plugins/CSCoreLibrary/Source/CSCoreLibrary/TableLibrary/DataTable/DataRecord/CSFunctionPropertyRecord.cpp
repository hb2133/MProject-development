#include "CSFunctionPropertyRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSFunctionPropertyRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);	
	_Parser.TryGetValue_bool(FString("enable"),nRowIdx,m_bEnable);
}
