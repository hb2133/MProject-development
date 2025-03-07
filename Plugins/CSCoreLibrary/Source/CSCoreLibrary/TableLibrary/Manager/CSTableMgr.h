// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "TableLibrary/Define/CSCommon_FunctionProperty.h"
#include "CSTableMgr.generated.h"

DECLARE_EVENT_OneParam(UCSTableMgr,FLocalChange,nLocalType::en)


class MCStringTableDetailRecord;
/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSTableMgr : public UCSBaseManager
{
	GENERATED_BODY()
public:
	FLocalChange LocalChange;
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Load() override;
	virtual void Release() override;
public:
	nLocalType::en GeteLocalType(){return m_eLocalType;}
	void SetLocalType(nLocalType::en _elocaltype);
	TArray<MCStringTableDetailRecord*> GetarrStringTableRecord(){return m_arrStringTableRecord;}

private:
	nLocalType::en m_eLocalType = nLocalType::KO;

	TArray<MCStringTableDetailRecord*> m_arrStringTableRecord;

};

#define g_TableMgrValid ( g_GameGlobal->IsValidManager<UCSTableMgr>() )
#define g_TableMgr ( g_GameGlobal->GetManager<UCSTableMgr>() )