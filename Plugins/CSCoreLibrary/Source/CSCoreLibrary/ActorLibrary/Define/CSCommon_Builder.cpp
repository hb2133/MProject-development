
#include "CSCommon_Builder.h"
#include "ActorLibrary/DataTable/DataManager/CSActorRecordMgr.h"

SCreationInfo::SCreationInfo(const FVector& _vActorPos, const FRotator& _rActorRot,
                                             const UNIQUEID& _nActorID, const FString& _strSpawnID, const FString& _strSpawnBPName)
: m_vActorPos(_vActorPos)
, m_rActorRot(_rActorRot)
, m_nActorID(_nActorID)
, m_strSpawnID(_strSpawnID)
, m_strSpawnBPName(_strSpawnBPName)
{
}

SCreationInfo::SCreationInfo(const FVector& _vActorPos, const FRotator& _rActorRot, const FString& _strSpawnBPName)
: m_vActorPos(_vActorPos)
, m_rActorRot(_rActorRot)
, m_strSpawnBPName(_strSpawnBPName)
{
}

//:: 테이블을 생성할때 등록
STableInfo::STableInfo(CSActorRecord* _pActorTbl)
: m_pActorTbl(_pActorTbl)
{
}

//:: 테이블 TID만 생성할때 등록 (테이블 로드는 받은 TID로 찾아서 등록)
STableInfo::STableInfo(const FString& _strActorTid)
: m_strActorTid(_strActorTid)
{
    m_pActorTbl = g_ActorRecordMgr->FindRecord(_strActorTid);	
}