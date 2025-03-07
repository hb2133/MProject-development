#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h" 
#include "..\DataRecord\CSPopupRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class CSCORELIBRARY_API CSPopupRecordMgr : public CSBaseRecordMgr<CSPopupRecordMgr, CSPopupRecord>
{
public:
	CSPopupRecordMgr();
	~CSPopupRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, CSPopupRecord* _pRecord) override;
};

#define g_PopupRecordMgr ( CSPopupRecordMgr::GetInstance() )