// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Define/CSActorCommon.h"

class CSActorShell;
class CSActorRecord;

class CSCORELIBRARY_API CSShellComponent
{
public:
	CSShellComponent(CSActorShell* _pOwner, const EShellComponentType& _eType);
	virtual ~CSShellComponent();

public:
//	virtual void OnReconnected() = 0;
	virtual bool OnCreate() = 0;
	virtual void Tick(float _dt) = 0;
	virtual void Release();

public:
	virtual CSActorShell* GetOwner();
	CSActorRecord* GetActorRecord();
	EShellComponentType& GetShellCompType();

protected:
	EShellComponentType m_eCompType = EShellComponentType::Max;
	CSActorShell* m_pOwner = nullptr;
};
