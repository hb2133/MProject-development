#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Define/CSClientDefine.h"

class CSActorRecord;

struct CSCORELIBRARY_API SCreationInfo
{

public:
    SCreationInfo() {}
    SCreationInfo(const FVector& _vActorPos, const FRotator& _rActorRot, const UNIQUEID& _nActorID, const FString& _strSpawnID, const FString& _strSpawnBPName);
    SCreationInfo(const FVector& _vActorPos, const FRotator& _rActorRot, const FString& _strSpawnBPName);

public:
    operator FVector() const { return this->m_vActorPos; }
    operator FRotator() const { return this->m_rActorRot; }

public:
    FVector m_vActorPos = FVector::ZeroVector;
    FRotator m_rActorRot = FRotator::ZeroRotator;
    UNIQUEID m_nActorID = INVALID_UNIQUEID;
    FString m_strSpawnID = FString("");
    
public:
    FString m_strSpawnBPName = FString("");
};

struct CSCORELIBRARY_API STableInfo
{
public:
    STableInfo() {}
    STableInfo(CSActorRecord* _pActorTbl);
    STableInfo(const FString& _strActorTid);
    
public:
    operator CSActorRecord* () const { return this->m_pActorTbl; }
    operator const FString () const { return this->m_strActorTid; }

public:
    CSActorRecord* m_pActorTbl = nullptr;
    FString m_strActorTid = FString("");
};
