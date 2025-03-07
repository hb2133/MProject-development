#pragma once
#include "ActorLibrary/Manager/CSActorMgr.h"

#include "ActorLibrary/Actor/Shell/CSActorShell.h"
#include "ActorLibrary/DataTable/DataRecord/CSActorRecord.h"


template<class TActorType>
TActorType* CSActorBuilder::BuildActor(const EActorBuilderType& _eBuilderType, const FName& _strActorTid, const FVector& _vActorPos /*= FVector::ZeroVector*/, const FRotator& _rActorRot /*= FRotator::ZeroRotator*/)
{
	if (g_ActorMgrValid)
	{
		STableInfo _stTableInfo(_strActorTid.ToString());
		if (_stTableInfo.m_pActorTbl)
		{
			SCreationInfo _stCreationInfo(_vActorPos, _rActorRot, _stTableInfo.m_pActorTbl->_strSpawnBPName.ToString());
			return g_ActorMgr->CreateActor<TActorType>(_eBuilderType, _stTableInfo, _stCreationInfo);
		}
	}
	
	return nullptr;
}

template <class ShellCompType>
bool CSActorBuilder::AppendComponent(CSActorShell* _pOwner)
{
	bool _bResult = false;
	TSharedPtr<ShellCompType> _pSharedShellComponent =  MakeShareable(new ShellCompType(_pOwner));
	if(ShellCompType* _pShellComponent = _pSharedShellComponent.Get())
	{
		_bResult = _pShellComponent->OnCreate();
		if (_bResult)
			_pOwner->m_ShellComponents.Add(_pShellComponent->GetShellCompType(), _pSharedShellComponent);
	}
	return _bResult;
}
