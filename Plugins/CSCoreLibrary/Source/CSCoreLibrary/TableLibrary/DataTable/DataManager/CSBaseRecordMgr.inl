// Fill out your copyright notice in the Description page of Project Settings.

template <typename T, typename TRecord>
void CSBaseRecordMgr<T, TRecord>::Release()
{
	ReleaseRecord();
}

template <typename T, typename TRecord>
bool CSBaseRecordMgr<T, TRecord>::LoadFromCSVTable(const FString& _filePath, const int& _nTbLayerIdx)
{
	CSDataTable _DataTable;
	CSCSVParser _Parser;
	if (_Parser.ReadCSVFile(_filePath))
	{
		_DataTable.ReleaseTable();
		FString _tid;

		//:: Read Records		
		for (int i = 1; i < _Parser.GetRowCount(); i++)
		{
			_Parser.GetRowTid(i, _tid);
			if(_tid.Contains(";"))			
				continue;	
			
			this->ParseData(_tid, i, _DataTable, _Parser);			
		}
		m_DataTableMap.Add(_nTbLayerIdx, _DataTable);
		return true;
	}
	return false; //:: Load CSV Fail
}

template <typename T, typename TRecord>
void CSBaseRecordMgr<T, TRecord>::ReleaseRecord()
{
	for (auto iter : m_DataTableMap)
		iter.Value.ReleaseTable();
	m_DataTableMap.Empty();
}

template <typename T, typename TRecord>
bool CSBaseRecordMgr<T, TRecord>::ParseData(FString& _strTid, int& _nIdx, CSDataTable& _DataTable, CSCSVParser& _Parser)
{
	_strTid.ToLowerInline();

	//:: 여기서 Tid 값 유효성 체크 (중복, 들어가면 안되는 값 등...)
	//:: Check Key Value Overlap
	if (_DataTable.m_RowRecords.Contains(_strTid))
	{
		UE_LOG(LogTemp, Log, TEXT("CSDataTable::ParseData - Table Tid Is Overlaped : %s"), *_strTid);
		return false;
	}

	TSharedPtr<TRecord> record = MakeShareable(new TRecord);
	record->ReadCSVData(_strTid, _nIdx, _Parser);

	_DataTable.m_RowRecords.Add(_strTid, record);
	_DataTable.m_Keys.Add(_strTid);

	AddRecord(_strTid, _nIdx, record.Get());
	return true;
}

template <typename T, typename TRecord>
TRecord* CSBaseRecordMgr<T, TRecord>::FindRecord(const FString& _strTid, const int& _nTbLayerIdx)
{
	if (m_DataTableMap.Contains(_nTbLayerIdx))
	{
		CSDataTable _DataTable = m_DataTableMap.FindRef(_nTbLayerIdx);
		CSBaseRecord* _pRecord = _DataTable.m_RowRecords.FindRef(_strTid).Get();

		return static_cast<TRecord*>(_pRecord);
	}
	return nullptr;
}

template <typename T, typename TRecord>
int32 CSBaseRecordMgr<T, TRecord>::FindRecordIdx(const FString& _strTid, const int& _nTbLayerIdx)
{
	if (m_DataTableMap.Contains(_nTbLayerIdx))
	{
		CSDataTable _DataTable = m_DataTableMap.FindRef(_nTbLayerIdx);
		return _DataTable.m_Keys.IndexOfByKey(_strTid);
	}
	return INVALID_UNIQUEID;
}

template <typename T, typename TRecord>
bool CSBaseRecordMgr<T, TRecord>::GetAllRecord(TArray<TRecord*>& _arrRecords, const int& _nTbLayerIdx)
{
	if (m_DataTableMap.Contains(_nTbLayerIdx))
	{
		CSDataTable _DataTable = m_DataTableMap.FindRef(_nTbLayerIdx);
		_arrRecords.Empty();

		for (auto iter : _DataTable.m_RowRecords)
		{
			CSBaseRecord* _pRecord = iter.Value.Get();
			_arrRecords.Add(static_cast<TRecord*>(_pRecord));
		}
		return true;
	}
	return false;
}
