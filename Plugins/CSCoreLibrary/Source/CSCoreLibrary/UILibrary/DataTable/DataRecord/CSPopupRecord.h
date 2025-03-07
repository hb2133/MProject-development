#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Define//CSCommon_GameMsg.h"

#include "TableLibrary/DataTable/DataRecord/CSBaseRecord.h"

class CSCORELIBRARY_API CSPopupRecord : public CSBaseRecord
{
public:
	nGameMsgType::en m_eMsgType;
	nPopupShowButtonType::en m_eShowButtonType;
	FString m_strTitle;
	FString m_strMsgDesc;
	FString m_strIconName;
	FString m_strOKLocal;
	FString m_strCancelLocal;
	FString m_strBackgroundName;
	FString m_strPrizeBackGroundName;
	

public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);
};
