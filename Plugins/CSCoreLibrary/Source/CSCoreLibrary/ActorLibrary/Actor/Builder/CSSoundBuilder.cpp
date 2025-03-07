// Fill out your copyright notice in the Description page of Project Settings.


#include "CSSoundBuilder.h"

#include "ActorLibrary//Actor/Sound/CSAmbientSound.h"
#include "ActorLibrary/Manager/CSActorMgr.h"
#include "CoreLibrary/Manager/CSFileManager.h"

ACSAmbientSound* CSSoundBuilder::BuildActor(const FName& _strActorTid, const FVector& _vActorPos /*= FVector::ZeroVector*/, const FRotator& _rActorRot /*= FRotator::ZeroRotator*/)
{
	return CSActorBuilder::BuildActor<ACSAmbientSound>(CSSoundBuilder::GetBuilderType(), _strActorTid, _vActorPos, _rActorRot);
}

void CSSoundBuilder::Release()
{
	CSActorBuilder::Release();
}

CSActorShell* CSSoundBuilder::BuildShell(const STableInfo& _stTblInfo, const SCreationInfo& _stCreationInfo)
{
	CSActorShell* _pShell = nullptr;

	if (UWorld* _pWorld = g_GameGlobal->GetCurWorld())
	{
		if (ACSAmbientSound* _pAmbientSound = _pWorld->SpawnActor<ACSAmbientSound>(ACSAmbientSound::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
			_pShell = _pAmbientSound;
	}
	return _pShell;
}
bool CSSoundBuilder::BuildShellComponents(const STableInfo& _stTblInfo, const SCreationInfo& _stCreationInfo, CSActorShell* _pOwner)
{
	return true;
}