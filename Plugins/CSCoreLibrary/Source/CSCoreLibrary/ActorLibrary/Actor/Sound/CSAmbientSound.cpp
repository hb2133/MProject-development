// Fill out your copyright notice in the Description page of Project Settings.


#include "CSAmbientSound.h"

#include "Components/AudioComponent.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "ResourceLibrary/Manager/CSAssetManager.h"
#include "Sound/SoundCue.h"

ACSAmbientSound::ACSAmbientSound()
: CSActorShell(this)
{
}

void ACSAmbientSound::BeginPlay()
{
	Super::BeginPlay();
	CSActorShell::OnBeginPlay();
}

void ACSAmbientSound::EndPlay(EEndPlayReason::Type _eReason)
{
	Super::EndPlay(_eReason);
}

void ACSAmbientSound::OnCreate()
{
	CSActorShell::OnCreate();
}

void ACSAmbientSound::Reclaim()
{
	CSActorShell::Reclaim();
}

void ACSAmbientSound::Destroyed()
{
	Super::Destroyed();
}

void ACSAmbientSound::BeginDestroy()
{
	Super::BeginDestroy();
	CSActorShell::OnBeginDestroy();
}

void ACSAmbientSound::Tick(float _dt)
{
	Super::Tick(_dt);
	CSActorShell::Tick(_dt);
}

void ACSAmbientSound::SetSound(const FName& _strSoundTid)
{
	if(UAudioComponent* _pAudioComp = GetAudioComponent())
	{
		if(g_AssetMgrValid)
		{
			if(USoundCue* pSoundCue = g_FileMgr->LoadObject<USoundCue>(nResourceType::General,_strSoundTid))
			{
				_pAudioComp->SetSound(pSoundCue);
			}
		}
	}
}

void ACSAmbientSound::SetTTSSound(const FName& _strSoundTid)
{
	if(UAudioComponent* _pAudioComp = GetAudioComponent())
	{
		if(g_AssetMgrValid)
		{
			if(USoundCue* pSoundCue = g_FileMgr->LoadObject<USoundCue>(nResourceType::General,_strSoundTid))
			{
				_pAudioComp->SetSound(pSoundCue);
			}
		}
	}
}

FString ACSAmbientSound::GetSoundName()
{
	if(UAudioComponent* _pAudioComp = GetAudioComponent())
	{
		if(_pAudioComp->GetSound())
		{
			return _pAudioComp->GetSound()->GetName();
		}

	}
	return "";
}
