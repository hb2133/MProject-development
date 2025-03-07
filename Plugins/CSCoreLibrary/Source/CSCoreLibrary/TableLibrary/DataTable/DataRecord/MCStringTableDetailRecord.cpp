#include "MCStringTableDetailRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void MCStringTableDetailRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	
	_Parser.TryGetValue(FString("KO"), nRowIdx, m_strKO);
	_Parser.TryGetValue(FString("EN"), nRowIdx, m_strEN);
}
