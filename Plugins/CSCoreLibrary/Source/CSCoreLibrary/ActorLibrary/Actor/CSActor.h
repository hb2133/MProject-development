// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorLibrary/Actor/Shell/CSActorShell.h"
#include "CSActor.generated.h"

UCLASS()
class CSCORELIBRARY_API ACSActor : public AActor, public CSActorShell
{
	GENERATED_BODY()

public:
	ACSActor();

	TWeakObjectPtr<AActor> m_pGuideActor;


public:
	virtual void Interaction();
protected:
	virtual void PostActorCreated() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type _eReason) override;

	virtual void OnCreate() override;

	virtual void Reclaim() override;
	virtual void Destroyed() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float _dt) override;
};
