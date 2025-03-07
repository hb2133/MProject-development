#pragma once

#include "CoreMinimal.h"
#include "../DataRecord/MPCustomizeSpriteRecord.h"
#include "TableLibrary/DataTable/DataManager/CSBaseRecordMgr.h"

class MPCustomizeSpriteRecordMgr : public CSBaseRecordMgr<MPCustomizeSpriteRecordMgr, MPCustomizeSpriteRecord>
{
public:
	MPCustomizeSpriteRecordMgr();
	~MPCustomizeSpriteRecordMgr();

public:
	virtual void Load() override;
	virtual void Release() override;

public:
	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, MPCustomizeSpriteRecord* _pRecord) override;

	static FString GetSpriteName(const FString& _strTid);
};

#define g_MPCustomizeSpriteRecordMgr ( MPCustomizeSpriteRecordMgr::GetInstance() )