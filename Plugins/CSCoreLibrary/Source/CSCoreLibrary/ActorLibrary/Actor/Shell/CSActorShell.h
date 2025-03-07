// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSCoreLibrary/ActorLibrary/Define/CSActorCommon.h"
#include "CSCoreLibrary/ActorLibrary/Define/CSCommon_Builder.h"

class AActor;
class USkeletalMeshComponent;
class UCSAnimInstance;
class CSShellComponent;

class CSCORELIBRARY_API CSActorShell
{
	friend class CSActorBuilder;

protected:
	virtual void OnReconnected();
	virtual void OnCreate();
	virtual void OnBeginPlay();
	virtual void OnBeginDestroy();
	virtual void OnEndOfPlay();

	virtual void Reclaim();

public:
	void Tick(const float& _dt);

public:
	CSActorShell(AActor* _pUnrealActor = nullptr);
	virtual ~CSActorShell();

public:
	//	int32 GetDBKey() { return 0; }
	int32 GetActorID() const { return 0; }
	FString GetActorTid() { return m_TableInfo.m_strActorTid; }
	FName GetModelID() { return NAME_None; }
	FName GetSpawnID() { return NAME_None; }

public:
	template <class TShellType>
	TShellType* ConvertShell();
	template <typename TCompType>
	TCompType* GetComponent(EShellComponentType _eCompType);

	template <typename TCompType>
	TCompType* GetUnrealComponent();
	template <typename TCompType>
	TArray<TCompType*> GetUnrealComponents(bool bIncludeFromChildActors = false);
	template <typename TCompType>
	TArray<TCompType*> GetUnrealComponentsByTag(const FName& _strTag);
	template <typename TCompType>
	TCompType* GetUnrealComponentsByTagUnique(const FName& _strTag);

	template <typename TCompType>
	TCompType* AppendUnrealComponent(const FName& _strComponentName, const FName& _strTag = NAME_None);

	void SetTableInfo(const STableInfo& _TableInfo) { m_TableInfo = _TableInfo; }

protected:
	AActor& m_UEActor;
	TMap<EShellComponentType, TSharedPtr<CSShellComponent>> m_ShellComponents;
	STableInfo m_TableInfo;
};

#include "CSActorShell.inl"