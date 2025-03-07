#include "CSPopupRecord.h"
#include "TableLibrary/DataParser/CSCSVParser.h"

void CSPopupRecord::ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser)
{
	CSBaseRecord::ReadCSVData(strTid, nRowIdx, _Parser);

	FString _strMsgType;
	_Parser.TryGetValue(FString("MsgType"), nRowIdx, _strMsgType);
	m_eMsgType = nGameMsgType::GetEnum(_strMsgType,false);
	
	FString _strShowButtonType;
	_Parser.TryGetValue(FString("ShowButtonType"), nRowIdx, _strShowButtonType);
	m_eShowButtonType = nPopupShowButtonType::GetEnum(_strShowButtonType,false);
	
	_Parser.TryGetValue(FString("OKLocal"), nRowIdx, m_strOKLocal);
	_Parser.TryGetValue(FString("CancelLocal"), nRowIdx, m_strCancelLocal);
	_Parser.TryGetValue(FString("TitleLocal"), nRowIdx, m_strTitle);
	_Parser.TryGetValue(FString("MsgDesc"), nRowIdx, m_strMsgDesc);
	_Parser.TryGetValue(FString("IconName"), nRowIdx, m_strIconName);
	_Parser.TryGetValue(FString("BackGroundName"), nRowIdx, m_strBackgroundName);
	_Parser.TryGetValue(FString("PrizeBackGroundName"), nRowIdx, m_strPrizeBackGroundName);	
}
