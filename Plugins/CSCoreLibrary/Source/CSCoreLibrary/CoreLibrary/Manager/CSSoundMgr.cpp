#include "CSSoundMgr.h"

#include "CSFileManager.h"
#include "ActorLibrary/Actor/Builder/CSSoundBuilder.h"
#include "ActorLibrary/Actor/Sound/CSAmbientSound.h"
#include "Components/AudioComponent.h"
#include "ResourceLibrary/DataTable/DataManager/CSSoundResourceRecordMgr.h"
#include "ResourceLibrary/Manager/CSAssetManager.h"
#include "Sound/SoundCue.h"

void UCSSoundMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSSoundMgr::Deinitialize()
{
	Super::Deinitialize();
}

void UCSSoundMgr::InitSound(const FName& _strBGMTid)
{
	if(ACSAmbientSound* _pSoundActor = CSSoundBuilder::BuildActor(FName("Ambient_Sound")))
	{
		m_pAmbientSound = _pSoundActor;
		if(_strBGMTid.IsNone() == false)
		{
			m_pAmbientSound->SetSound(_strBGMTid);
			m_pAmbientSound->Play();
			if(m_IsBGMMute)
			{
				if(m_pAmbientSound->GetAudioComponent())
				{
					m_pAmbientSound->GetAudioComponent()->SetVolumeMultiplier(0.f);
				}
			}
		}
	}
	if(ACSAmbientSound* _pButtonSoundActor = CSSoundBuilder::BuildActor(FName("Ambient_Sound")))
	{
		m_pButtonAmbientSound = _pButtonSoundActor;

		//m_pButtonAmbientSound->SetSound("SwitchOn_Sound_Que");
		if(m_pButtonAmbientSound->GetAudioComponent())
		{
			m_pButtonAmbientSound->GetAudioComponent()->SetPitchMultiplier(1.f);
			m_pButtonAmbientSound->GetAudioComponent()->SetVolumeMultiplier(2.0f);
			if(m_IsEffectMute)
			{
				m_pButtonAmbientSound->GetAudioComponent()->SetVolumeMultiplier(0.f);
			}
		}

	
	}

	if(ACSAmbientSound* _pButtonSoundActor = CSSoundBuilder::BuildActor(FName("Ambient_Sound")))
	{
		m_pTTSAbientSound = _pButtonSoundActor;

		//m_pButtonAmbientSound->SetSound("SwitchOn_Sound_Que");
		if(m_pTTSAbientSound->GetAudioComponent())
		{
			m_pTTSAbientSound->GetAudioComponent()->SetPitchMultiplier(1.f);
			m_pTTSAbientSound->GetAudioComponent()->SetVolumeMultiplier(2.0f);
			
		}
	}

	if(ACSAmbientSound* _pButtonSoundActor = CSSoundBuilder::BuildActor(FName("Ambient_Sound")))
	{
		m_pEffectAmbientSound = _pButtonSoundActor;

		//m_pButtonAmbientSound->SetSound("SwitchOn_Sound_Que");
		if(m_pEffectAmbientSound->GetAudioComponent())
		{
			m_pEffectAmbientSound->GetAudioComponent()->SetPitchMultiplier(1.f);
			m_pEffectAmbientSound->GetAudioComponent()->SetVolumeMultiplier(2.0f);
		}
		
	}
}

void UCSSoundMgr::Release()
{
	Super::Release();
}

void UCSSoundMgr::Load()
{
	Super::Load();
	
}

void UCSSoundMgr::Tick(float _dt)
{
	Super::Tick(_dt);
}

void UCSSoundMgr::PlaySound2D(const FString& _strSoundName)
{	
	if(m_pAmbientSound.IsValid() == false) return;
	
	m_pAmbientSound->SetSound(FName(*_strSoundName));
	m_pAmbientSound->Play();

	
}

void UCSSoundMgr::ButtonPlaySound(float _StartTime, FString _SoundQue)
{
	if(m_pButtonAmbientSound.IsValid() == false) return;

	m_pButtonAmbientSound->SetSound(FName(*_SoundQue));
	m_pButtonAmbientSound->Play(_StartTime);
}

void UCSSoundMgr::TTSPlaySound(float _StartTime, FString _SoundQue)
{
	if(m_pTTSAbientSound.IsValid() == false) return;
	
	m_pTTSAbientSound->SetTTSSound(FName(*_SoundQue));
	m_pTTSAbientSound->Play(_StartTime);
	
}

void UCSSoundMgr::EffectPlaySound(float _StartTime, FString _SoundQue)
{
	if(m_pEffectAmbientSound.IsValid() == false) return;
	
	m_pEffectAmbientSound->SetTTSSound(FName(*_SoundQue));
	m_pEffectAmbientSound->Play(_StartTime);
}

void UCSSoundMgr::StopEffectSound()
{
	if(m_pEffectAmbientSound.IsValid() == false) return;

	m_pEffectAmbientSound->Stop();
}

void UCSSoundMgr::StopTTSSound()
{
	if(m_pTTSAbientSound.IsValid() == false) return;

	m_pTTSAbientSound->Stop();
}

void UCSSoundMgr::Stop()
{
	if(m_pAmbientSound.IsValid() == false) return;
	
	m_pAmbientSound->Stop();
}

void UCSSoundMgr::TTSReplay()
{
	if(m_pTTSAbientSound.IsValid() == false) return;

	m_pTTSAbientSound->Play();
}

UAudioComponent* UCSSoundMgr::GetTTSAudioComp()
{
	if(m_pTTSAbientSound.IsValid())
	{
		if(m_pTTSAbientSound->GetAudioComponent())
		{
			return m_pTTSAbientSound->GetAudioComponent();
		}
	}
	return nullptr;
}

UAudioComponent* UCSSoundMgr::GetEffectAudioComp()
{
	if(m_pEffectAmbientSound.IsValid())
	{
		if(m_pEffectAmbientSound->GetAudioComponent())
		{
			return m_pEffectAmbientSound->GetAudioComponent();
		}
	}
	return nullptr;
}

FString UCSSoundMgr::GetEffectSoundName()
{
	if(m_pEffectAmbientSound.IsValid() == false) return "";

	return m_pEffectAmbientSound->GetSoundName();
}

void UCSSoundMgr::SetBGMVolume(float _volume)
{
	if(m_pAmbientSound.IsValid())
	{
		if(m_pAmbientSound->GetAudioComponent())
		{
			if(!m_IsBGMMute)
			{
				m_pAmbientSound->GetAudioComponent()->SetVolumeMultiplier(_volume);
			}
		}
	}
}

void UCSSoundMgr::SetBtnVolume(float _volume)
{
	if(m_pButtonAmbientSound.IsValid())
	{
		if(m_pButtonAmbientSound->GetAudioComponent())
		{
			m_pButtonAmbientSound->GetAudioComponent()->SetVolumeMultiplier(_volume);
		}
	}
}

void UCSSoundMgr::SetBGMMute(bool _enable)
{
	if(m_pAmbientSound.IsValid())
	{
		if(m_pAmbientSound->GetAudioComponent())
		{
			m_pAmbientSound->GetAudioComponent()->SetVolumeMultiplier(_enable ? 0.f:1.f);
			m_IsBGMMute = _enable;
		}
	}
}

void UCSSoundMgr::SetEffectMute(bool _enable)
{
	if(m_pButtonAmbientSound.IsValid())
	{
		if(m_pButtonAmbientSound->GetAudioComponent())
		{
			m_pButtonAmbientSound->GetAudioComponent()->SetVolumeMultiplier(_enable ? 0.f:2.f);
			m_IsEffectMute = _enable;
		}
	}
}

void UCSSoundMgr::SetBtnMute(bool _enable)
{
	if(m_pButtonAmbientSound.IsValid())
	{
		if(m_pButtonAmbientSound->GetAudioComponent())
		{
			m_pButtonAmbientSound->GetAudioComponent()->SetVolumeMultiplier(_enable ? 0.f:1.f);
			m_IsBtnMute = _enable;
		}
	}
}
