

#include "TableLibrary/Manager/CSTableMgr.h"
#include "TableLibrary/DataTable/DataManager/MCStringTableDataRecordMgr.h"


void UCSTableMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSTableMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UCSTableMgr::Load()
{
	Super::Load();

	g_StringTableDataRecordMgr->GetAllRecord(m_arrStringTableRecord);
}

void UCSTableMgr::Release()
{
	Super::Release();
}

void UCSTableMgr::SetLocalType(nLocalType::en _elocaltype)
{
	if(m_eLocalType == _elocaltype)
		m_eLocalType = nLocalType::KO;
	else
		m_eLocalType = nLocalType::EN;

	if(LocalChange.IsBound())
	{
		LocalChange.Broadcast(m_eLocalType);
	}
}
