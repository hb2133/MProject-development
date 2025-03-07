// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "MProjectMgr.generated.h"

/**
 * 
 */
UCLASS()
class MPROJECT_API UMProjectMgr : public UCSBaseManager
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Load() override;
	virtual void Release() override;
	virtual void Tick(float DeltaTime) override;

public:
	void StartPlayRun();
	void StartPlayDigging();
	void CreateRunningScore();
	void CreateDriggerScore();
	
	void SetScore(float score);
	float GetScore(){ return m_fScore; }
	void SetCurrentTime(int32 currenttime) { m_iCurrentTime = currenttime; }
	int32 GetCurrentTime(){ return m_iCurrentTime; }
	void SetDriggerScore(int32 driggerscore) { m_iDriggerScore = driggerscore; }
	int32 GetDriggerScore(){ return m_iDriggerScore; }
	void SetClearMoney(int32 clearmoney) { m_iClearMoney = clearmoney; }
	int32 GetClearMoney(){ return m_iClearMoney; }
	void SetClearExp(int32 clearexp) { m_iClearExp = clearexp; }
	int32 GetClearExp(){ return m_iClearExp; }
private:
	float m_fScore;
	int32 m_iCurrentTime;
	int32 m_iDriggerScore;
	int32 m_iClearMoney;
	int32 m_iClearExp;
};

#define g_MProjectMgrValid ( g_GameGlobal->IsValidManager<UMProjectMgr>() )
#define g_MProjectMgr ( g_GameGlobal->GetManager<UMProjectMgr>() )
