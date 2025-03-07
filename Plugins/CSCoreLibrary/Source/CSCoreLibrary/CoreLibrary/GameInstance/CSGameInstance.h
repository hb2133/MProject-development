// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSGameInstance.generated.h"

UCLASS()
class CSCORELIBRARY_API UCSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init();
	virtual void Shutdown();
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld);

	virtual void InitGameActorBuilder() {}
	virtual void InitLevelManageType() {}

protected:
	void LoadData();
	void ReleaseData();

public:
	FString GetOldLevelName() { return m_strOldLevelName; }
	FString GetCurLevelName() { return m_strCurLevelName; }

protected:
	FThreadSafeBool m_bGameInstInit = false;
	FString m_strOldLevelName = FString("");
	FString m_strCurLevelName = FString("");
};

// 주형님 백업
//FString NetworkErrorMsg;
//ENetworkFailure::Type NetworkFailureType;

//FORCEINLINE const FString& GetNetworkErrorMsg() const { return NetworkErrorMsg; }

//private:
//	UFUNCTION()
//	void OnNetworkFailed(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorMessage);
//};
