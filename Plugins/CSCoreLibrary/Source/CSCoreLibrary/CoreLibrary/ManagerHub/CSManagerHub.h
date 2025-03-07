// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"

namespace ManagerHub
{
	CSEnumStruct EManageState
	{
		CSEnumDefault
		{
			eGlobalInit, //:: 전역으로 사용
			eLoginInit,
			eLobbyInit,
			ePlayInit,
			eMProject,
			Max,
		};

		CSEnumMapRegist
		{
			InsertMap(eLoginInit, "LoginInit");
			InsertMap(eLobbyInit, "LobbyInit");
			InsertMap(ePlayInit, "PlayInit");
			InsertMap(eMProject, "MProject");
		}
	}
}

class CSManagerHubInterface
{
public:
	virtual ~CSManagerHubInterface() {}
	virtual void InitManagers() = 0;
	virtual void LoadManager(const ManagerHub::EManageState::en& _eState) = 0;
	virtual void ReleaseManager(const ManagerHub::EManageState::en& _eState) = 0;
	virtual void ReleaseHub() = 0;
};

template<typename HubType, typename ManagerType, typename HubMgrID>
class CSManagerHub 
: public CSSingleton<HubType>
, public CSManagerHubInterface
{
public:
	CSManagerHub() {}
	~CSManagerHub() {}

public:
	virtual void Release() override;
	virtual void Load() override {}

public:
	virtual void InitManagers() {}

public:
	void Init(const ManagerHub::EManageState::en& _eState, const HubMgrID& _eMgrID, ManagerType* _pManager);
	void LoadManager(const ManagerHub::EManageState::en& _eState);
	void ReleaseManager(const ManagerHub::EManageState::en& _eState);
	void ReleaseHub() { this->Release(); }
	
protected:
	TMap<HubMgrID, ManagerType*> m_ManagerContainer[ManagerHub::EManageState::Max];
	ManagerHub::EManageState::en m_CurrentManageState = ManagerHub::EManageState::Max;
};

#include "CSManagerHub.inl"