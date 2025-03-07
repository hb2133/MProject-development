// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ActorLibrary/Actor/Shell/CSActorShell.h"

#include "ActorLibrary/Actor/Builder/CSActorBuilder.h"

#include "CSPawn.generated.h"

UCLASS()
class CSCORELIBRARY_API ACSPawn : public APawn, public CSActorShell
{
	GENERATED_BODY()

public:
	ACSPawn();

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
