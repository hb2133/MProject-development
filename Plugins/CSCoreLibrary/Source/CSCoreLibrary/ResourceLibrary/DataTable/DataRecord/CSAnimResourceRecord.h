// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceLibrary/DataTable/DataRecord/CSBaseResourceRecord.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"

class CSCORELIBRARY_API CSAnimResourceRecord : public CSBaseResourceRecord
{
public:
	virtual void ReadCSVData(FString strTid, int nRowIdx, CSCSVParser& _Parser);

	FORCEINLINE bool GetEnableStop() const {return m_bEnableStop;}
	FORCEINLINE bool GetEnablePlayInJump() const {return m_bEnablePlayInJump;}
private:
	bool m_bEnableStop;
	bool m_bEnablePlayInJump;
};
