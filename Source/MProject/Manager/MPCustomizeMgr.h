// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "MPCustomizeMgr.generated.h"

class MPCustomizeRecord;

UCLASS()
class MPROJECT_API UMPCustomizeMgr : public UCSBaseManager
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Load() override;
	virtual void Release() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	TArray<MPCustomizeRecord*> m_CustomizeItem;
	int32 m_ColumnMax;
};

#define g_MPCustomizeMgrValid ( g_GameGlobal->IsValidManager<UMPCustomizeMgr>() )
#define g_MPCustomizeMgr ( g_GameGlobal->GetManager<UMPCustomizeMgr>() )