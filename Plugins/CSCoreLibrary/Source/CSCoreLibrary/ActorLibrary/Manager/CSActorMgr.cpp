// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorLibrary/Manager/CSActorMgr.h"
#include "ActorLibrary/Actor/Shell/CSActorShell.h"

void UCSActorMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSActorMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UCSActorMgr::Release()
{
	for (auto& iter : m_pActorBuilder)
	{
		if (CSActorBuilder* _pBuilder = iter.Value.Get())
			_pBuilder->Release();
	}
	m_pActorBuilder.Empty();
}

void UCSActorMgr::Load()
{
}

void UCSActorMgr::Tick(float _dt)
{

}

void UCSActorMgr::AppendShellBuilder(const EActorBuilderType& _eBuilderType, CSActorShell* _pOwnerShell, const FName& _strActorTid /*= NAME_None*/)
{
	if (TSharedPtr<CSActorBuilder> _pSharedBuilder = m_pActorBuilder.FindRef(_eBuilderType))
	{
		if (CSActorBuilder* _pBuilder = _pSharedBuilder.Get())
		{
			SCreationInfo _stCreationInfo;
			STableInfo _stTableInfo(_strActorTid.ToString());
			_pOwnerShell->SetTableInfo(_stTableInfo);
			_pBuilder->BuildShellComponents(_stTableInfo, _stCreationInfo, _pOwnerShell);
		}
	}
}
