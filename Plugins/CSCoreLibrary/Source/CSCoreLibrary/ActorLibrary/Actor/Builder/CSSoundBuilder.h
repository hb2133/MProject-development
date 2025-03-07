// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/Builder/CSActorBuilder.h"

class ACSAmbientSound;

class CSCORELIBRARY_API CSSoundBuilder : public CSActorBuilder
{
public:
	static ACSAmbientSound* BuildActor(const FName& _strActorTid, const FVector& _vActorPos = FVector::ZeroVector, const FRotator& _rActorRot = FRotator::ZeroRotator);
	static EActorBuilderType GetBuilderType()
	{
		return EActorBuilderType::CSSoundBuilder;
	}

public:
	CSSoundBuilder() {}

public:
	virtual void Release();
	virtual CSActorShell* BuildShell(const STableInfo& _stTblInfo, const SCreationInfo& _stCreationInfo);
	virtual bool BuildShellComponents(const STableInfo& _stTblInfo, const SCreationInfo& _stCreationInfo, CSActorShell* _pOwner);
};
