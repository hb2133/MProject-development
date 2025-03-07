// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Define/CSCommon_Builder.h"
#include "ActorLibrary/Define/CSActorCommon.h"

class CSShellComponent;
class CSActorShell;
class CSActorRecord;

class CSCORELIBRARY_API CSActorBuilder
{
public:
	template<class TActorType>
	static TActorType* BuildActor(const EActorBuilderType& _eBuilderType, const FName& _strActorTid, const FVector& _vActorPos = FVector::ZeroVector, const FRotator& _rActorRot = FRotator::ZeroRotator);

	template <class ShellCompType>
	bool AppendComponent(CSActorShell* _pOwner);

public:
	CSActorBuilder() {}
	virtual ~CSActorBuilder() {}

public:
	virtual void Release();
	virtual CSActorShell* BuildShell(const STableInfo& _stTblInfo, const SCreationInfo& _stCreationInfo) { return nullptr; }
	virtual bool BuildShellComponents(const STableInfo& _stTblInfo, const SCreationInfo& _stCreationInfo, CSActorShell* _pOwner) { return false; }
};

#include "CSActorBuilder.inl"

//:: BuildShell은 내부에서 유연하게 액터를 생성하도록 한다.
//:: 작업할 기능에 따라 효율적인 생성방식이 다르기 때문이다.

//:: <예시>
//:: 1. BP를 로드하여 SpawnActor를 사용해 생성
//:: 2. 클래스로 직접 로드 (내부 코드를 사용하여 액터 생성되는 경우)
//:: 3. 풀링 매니저에 접근하여 생성할 수 있음
//:: 4. 타입에 따른 분기처리도 가능
