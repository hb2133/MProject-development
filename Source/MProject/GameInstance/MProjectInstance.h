// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/GameInstance/CSGameInstance.h"
#include "MProjectInstance.generated.h"

/**
 * 
 */
UCLASS()
class MPROJECT_API UMProjectInstance : public UCSGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init() override;
	virtual void OnStart() override;
	virtual void Shutdown() override;
	virtual void FinishDestroy() override;

	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	virtual void InitGameActorBuilder() override;
	virtual void InitLevelManageType() override;

public:
	// 임시 거처
	FString UUID;
};
