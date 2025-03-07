// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/Shell/CSActorShell.h"
#include "Sound/AmbientSound.h"
#include "CSAmbientSound.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API ACSAmbientSound : public AAmbientSound,public CSActorShell
{
	GENERATED_BODY()
public:
	ACSAmbientSound();
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type _eReason) override;

	virtual void OnCreate() override;

	virtual void Reclaim() override;
	virtual void Destroyed() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float _dt) override;
public:
	void SetSound(const FName& _strSoundTid);

	void SetTTSSound(const FName& _strSoundTid);

	FString GetSoundName();
};
