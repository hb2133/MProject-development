// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"
#include "CSBaseManager.generated.h"

UCLASS()
class CSCORELIBRARY_API UCSBaseManager : public UGameInstanceSubsystem ,public FTickableGameObject
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	virtual void OnLoadLevelPrev(UWorld* _pWorld, bool _bAbsolute) {}
	virtual void OnLoadLevelPost() {}
	virtual void Tick(float _deltaTime) override {}
	//virtual void OnReconnected() {} //:: 서버 있을때 고려해볼 옵션
	virtual void Load() {}
	virtual void Release() {}
	virtual TStatId GetStatId() const override {return TStatId();}
};
