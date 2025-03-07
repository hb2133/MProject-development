#include "MPCustomizeSpriteRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void MPCustomizeSpriteRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	_Parser.TryGetValue("SpriteName", nRowIdx, m_strSpriteName);
}