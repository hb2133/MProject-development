// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorLibrary/Actor/Shell/CSActorShell.h"
#include "ActorLibrary/Actor/Component/ShellComponent/CSShellComponent.h"
#include "GameFramework/Actor.h"


CSActorShell::CSActorShell(AActor* _pUnrealActor /*= nullptr*/)
	: m_UEActor(*_pUnrealActor)
{
}

CSActorShell::~CSActorShell()
{
}

void CSActorShell::OnReconnected()
{
}

void CSActorShell::OnCreate()
{
}

void CSActorShell::OnBeginPlay()
{
}

void CSActorShell::OnBeginDestroy()
{
	for (auto& iter : m_ShellComponents)
		iter.Value->Release();

	m_ShellComponents.Empty();
}

void CSActorShell::OnEndOfPlay()
{

}

void CSActorShell::Reclaim()
{
}

void CSActorShell::Tick(const float& _dt)
{
	for (auto& iter : m_ShellComponents)
		iter.Value->Tick(_dt);
}
