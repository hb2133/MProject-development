// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableLibrary/DataParser/CSCSVParser.h"
#include "TableLibrary/DataTable/CSDataTable.h"
#include "CoreLibrary/Define/CSClientDefine.h"

class CSRecordMgrInterface
{
public:
	virtual ~CSRecordMgrInterface() {}
	virtual void Load() = 0;
	virtual void Release() = 0;
};

template<typename T, typename TRecord>
class CSBaseRecordMgr : public CSRecordMgrInterface
{
public:
	CSBaseRecordMgr() {}
	~CSBaseRecordMgr() {}

public:
	virtual void Load() {}
	virtual void Release();

protected:
	bool LoadFromCSVTable(const FString& _filePath, const int& _nTbLayerIdx = 0);
	/*
	bool LoadFromBinTable(const FString& _filePath, const bool& _bUseAddRecordFunc = true, const int& _nTableIdx = 0) { return true; }
	*/
	void ReleaseRecord();

	virtual void AddRecord(const FString& _strTid, const int& _nRowIdx, TRecord* _pRecord) {}

private:
	bool ParseData(FString& _strTid, int& _nIdx, CSDataTable& _DataTable, CSCSVParser& _Parser);

public:
	TRecord* FindRecord(const FString& _strTid, const int& _nTbLayerIdx = 0);
	int32 FindRecordIdx(const FString& _strTid, const int& _nTbLayerIdx = 0);
	bool GetAllRecord(TArray<TRecord*>& _arrRecords, const int& _nTbLayerIdx = 0);

	template<typename TRecordType>
	TArray<TRecordType*> GetAllRecord_SpecificType(const int& _nTbLayerIdx = 0)
	{
		TArray<TRecordType*> _arrRecords;
		if (m_DataTableMap.Contains(_nTbLayerIdx))
		{
			CSDataTable _DataTable = m_DataTableMap.FindRef(_nTbLayerIdx);
			_arrRecords.Empty();

			for (auto iter : _DataTable.m_RowRecords)
			{
				CSBaseRecord* _pRecord = iter.Value.Get();
				_arrRecords.Add(static_cast<TRecordType*>(_pRecord));
			}
		}
		return _arrRecords;
	}

protected:
	TMap<int /*Table Layer ID*/, CSDataTable> m_DataTableMap;

/*-----------------------------------------------------------------------------
	Singleton Interface
-----------------------------------------------------------------------------*/
public:
 	static T* GetInstance()
 	{
 		if (m_pInst == nullptr)
 			m_pInst = new T;
 		return m_pInst;
 	}
 
 	static void Clear()
 	{
 		if (m_pInst != nullptr)
 		{
 			T* _pInst = m_pInst;
 			m_pInst = nullptr;
 			delete _pInst;
 		}
 	}
 
public:
	static T* m_pInst;
};

#include "CSBaseRecordMgr.inl"

template<typename T, typename TRecord>
T* CSBaseRecordMgr<T, TRecord>::m_pInst = nullptr;
