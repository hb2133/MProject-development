// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "CSMiniMapMgr.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMiniMapChange,const FString&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMiniMapMove,FVector2D,float);
/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSMiniMapMgr : public UCSBaseManager
{
	GENERATED_BODY()
public:
	FMiniMapChange MiniMapChange;
	FMiniMapMove MiniMapMove;
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void Load() override;
	virtual void Release() override;

public:
	void ChangeMap(const FString& _mapName);

	void MoveObject(const FVector2D& _position,float _angle);

private:
	
	
};
#define g_MiniMapMgrValid ( g_GameGlobal->IsValidManager<UCSMiniMapMgr>() )
#define g_MiniMapMgr ( g_GameGlobal->GetManager<UCSMiniMapMgr>() )