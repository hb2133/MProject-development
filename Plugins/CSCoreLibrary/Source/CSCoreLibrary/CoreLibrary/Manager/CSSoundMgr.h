// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/CSActor.h"
#include "ActorLibrary/Actor/Sound/CSAmbientSound.h"
#include "Components/AudioComponent.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "CSSoundMgr.generated.h"

class UAudioComponent;

UCLASS()
class CSCORELIBRARY_API UCSSoundMgr : public UCSBaseManager
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void InitSound(const FName& _strBGMTid);

	
public:
	void Release() override;
	void Load() override;
	void Tick(float _dt) override;

	void PlaySound2D(const FString& _strSoundName);
	void ButtonPlaySound(float _StartTime,FString _SoundQue);
	void TTSPlaySound(float _StartTime, FString _SoundQue);
	void EffectPlaySound(float _StartTime, FString _SoundQue);
	void StopEffectSound();
	void StopTTSSound();
	void Stop();

	void TTSReplay();
	UAudioComponent* GetTTSAudioComp();
	UAudioComponent* GetEffectAudioComp();
	
	FString GetEffectSoundName();

	void SetBGMVolume(float _volume);
	void SetBtnVolume(float _volume);
	
	void SetBGMMute(bool _enable);
	void SetEffectMute(bool _enable);
	void SetBtnMute(bool _enable);

	bool GetIsBGMMute(){return m_IsBGMMute;}
	bool GetIsEffectMute(){return m_IsEffectMute;}
	bool GetIsBtnMute(){return m_IsBtnMute;}

	FOnAudioFinished& GetPlaySoundFinish(){return m_pAmbientSound->GetAudioComponent()->OnAudioFinished;}
private:	
	TWeakObjectPtr<ACSAmbientSound> m_pAmbientSound;
	TWeakObjectPtr<ACSAmbientSound> m_pButtonAmbientSound;
	TWeakObjectPtr<ACSAmbientSound>
	m_pTTSAbientSound;
	TWeakObjectPtr<ACSAmbientSound> m_pEffectAmbientSound;;
	FString m_strCurrentPlayingBGMName;

	bool m_IsBGMMute = false;
	bool m_IsEffectMute = false;
	bool m_IsBtnMute = false;
};

#define g_SoundMgrValid ( g_GameGlobal->IsValidManager<UCSSoundMgr>() )
#define g_SoundMgr ( g_GameGlobal->GetManager<UCSSoundMgr>() )