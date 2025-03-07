#include "MPCustomizeRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

MPCustomizeRecord::~MPCustomizeRecord()
{
	delete m_pItemInfo;
	
	CSBaseRecord::~CSBaseRecord();
}

void MPCustomizeRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	m_pItemInfo = new ItemInfo();
	
	_Parser.TryGetValue("SpriteName", nRowIdx,m_pItemInfo->strSpriteName);
	_Parser.TryGetValue("CustomType", nRowIdx,m_pItemInfo->strCustomType);
	_Parser.TryGetValue("ItemType", nRowIdx,m_pItemInfo->strItemType);
	_Parser.TryGetValue_bool("Wearing", nRowIdx, m_pItemInfo->bIsWearing);
}
