// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/GameMode/CSGameModeBase.h"
#include "CoreLibrary/GameState/CSGameState.h"
#include "UObject/NoExportTypes.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "CoreLibrary/ManagerHub/CSManagerHub.h"
#include "CSGameGlobal.generated.h"

UCLASS()
class CSCORELIBRARY_API UCSGameGlobal : public UObject
{
	GENERATED_BODY()
	
public:
	UCSGameGlobal();
	~UCSGameGlobal();

public:
	void Load();
	void Release();

	void SetCurWorld(UWorld* _pWorld) { m_pWorld = _pWorld; }
	UWorld* GetCurWorld() { return m_pWorld.Get(); }

public:
	void InitHub(CSManagerHubInterface* _pManagerHub);
	void InitManagers();
	void LoadManager(const ManagerHub::EManageState::en& _eState);
	void ReleaseManager(const ManagerHub::EManageState::en& _eState);

public:
	ACSGameModeBase* GetGameMode();
	ACSGameState* GetGameState();

public:
	static UCSGameGlobal& Get()
	{
		return *Cast<UCSGameGlobal>(GEngine->GameSingleton);
	}

public:
	template <typename T>
	bool IsValidManager()
	{
		return (this->GetManager<T>() != nullptr);
	}

	template <typename T>
	T* GetManager()
	{
			if (UWorld* _pWorld = m_pWorld.Get())
				return ::Cast<T>(USubsystemBlueprintLibrary::GetGameInstanceSubsystem(_pWorld, T::StaticClass()));
		return nullptr;
	}

private:
	TWeakObjectPtr<UWorld> m_pWorld;
	TArray<CSManagerHubInterface*> m_pManagerHubInterface;
};

#define g_GameGlobal ( ::Cast<UCSGameGlobal>(GEngine->GameSingleton) )
