// Fill out your copyright notice in the Description page of Project Settings.

#include "MPCustomizeMgr.h"

#include "NavigationSystem.h"
#include "MProject/DataTable/DataManager/MPCustomizeRecordMgr.h"
#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"

void UMPCustomizeMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMPCustomizeMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UMPCustomizeMgr::Load()
{
	Super::Load();

	if (g_MPCustomizeRecordMgr)
	{
		g_MPCustomizeRecordMgr->GetAllRecord(m_CustomizeItem);
	}
	if (g_CSDefineRecordMgr)
	{
		m_ColumnMax = g_CSDefineRecordMgr->GetValue_Number("GV_CUSTOMIZE_COLUMN_MAX");
	}
}

void UMPCustomizeMgr::Release()
{
	Super::Release();
}

void UMPCustomizeMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}