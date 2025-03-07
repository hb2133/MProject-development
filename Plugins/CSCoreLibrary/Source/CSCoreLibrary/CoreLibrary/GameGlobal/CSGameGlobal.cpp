// Fill out your copyright notice in the Description page of Project Settings.


#include "CSGameGlobal.h"
#include "Kismet/GameplayStatics.h"

UCSGameGlobal::UCSGameGlobal()
{
}

UCSGameGlobal::~UCSGameGlobal()
{
}

void UCSGameGlobal::Load()
{

}

void UCSGameGlobal::Release()
{
	for (auto& iter : m_pManagerHubInterface)
		iter->ReleaseHub();

	m_pManagerHubInterface.Empty();
}

void UCSGameGlobal::InitHub(CSManagerHubInterface* _pManagerHub)
{
	m_pManagerHubInterface.Add(_pManagerHub);
}

void UCSGameGlobal::InitManagers()
{
	for (auto& iter : m_pManagerHubInterface)
		iter->InitManagers();
}

void UCSGameGlobal::LoadManager(const ManagerHub::EManageState::en& _eState)
{
	for (auto& iter : m_pManagerHubInterface)
		iter->LoadManager(_eState);
}

void UCSGameGlobal::ReleaseManager(const ManagerHub::EManageState::en& _eState)
{
	for (auto& iter : m_pManagerHubInterface)
		iter->ReleaseManager(_eState);
}

ACSGameModeBase* UCSGameGlobal::GetGameMode()
{
	if(UWorld* _pWorld = m_pWorld.Get())
		return ::Cast<ACSGameModeBase>(UGameplayStatics::GetGameMode(_pWorld));
	return nullptr;
}

ACSGameState* UCSGameGlobal::GetGameState()
{
	if(UWorld* _pWorld = m_pWorld.Get())
		return ::Cast<ACSGameState>(UGameplayStatics::GetGameState(_pWorld));
	return nullptr;
}
