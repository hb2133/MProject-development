// Fill out your copyright notice in the Description page of Project Settings.


#include "CSMiniMapMgr.h"


#include "TableLibrary/DataTable/DataManager/CSMiniMapRecordMgr.h"
#include "UILibrary/Manager/CSUIMgr.h"

void UCSMiniMapMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSMiniMapMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UCSMiniMapMgr::Load()
{
	Super::Load();
}

void UCSMiniMapMgr::Release()
{
	MiniMapChange.Clear();
	MiniMapMove.Clear();
	Super::Release();
}

void UCSMiniMapMgr::ChangeMap(const FString& _mapName)
{
	if(MiniMapChange.IsBound())
	{
		MiniMapChange.Broadcast(_mapName);
	}
}

void UCSMiniMapMgr::MoveObject(const FVector2D& _position, float _angle)
{
	if(MiniMapMove.IsBound())
	{
		MiniMapMove.Broadcast(_position,_angle);
	}
}


