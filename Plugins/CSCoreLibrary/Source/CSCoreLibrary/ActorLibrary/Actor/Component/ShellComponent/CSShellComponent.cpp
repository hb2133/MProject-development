// Fill out your copyright notice in the Description page of Project Settings.

#include "CSShellComponent.h"

CSShellComponent::CSShellComponent(CSActorShell* _pOwner, const EShellComponentType& _eType)
: m_eCompType(_eType),
  m_pOwner(_pOwner)
{
}

CSShellComponent::~CSShellComponent()
{
}

void CSShellComponent::Release()
{
	m_pOwner = nullptr;
}

CSActorShell* CSShellComponent::GetOwner()
{
	return m_pOwner;
}

CSActorRecord* CSShellComponent::GetActorRecord()
{
	return nullptr;
}

EShellComponentType& CSShellComponent::GetShellCompType()
{
	return m_eCompType;
}