// Fill out your copyright notice in the Description page of Project Settings.


#include "CSActor.h"
#include "Components/SkeletalMeshComponent.h"

ACSActor::ACSActor()
	: CSActorShell(this)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACSActor::Interaction()
{
}

void ACSActor::PostActorCreated()
{
	Super::PostActorCreated();
}

void ACSActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACSActor::BeginPlay()
{
	Super::BeginPlay();
	CSActorShell::OnBeginPlay();
}

void ACSActor::EndPlay(EEndPlayReason::Type _eReason)
{
	Super::EndPlay(_eReason);
	CSActorShell::OnEndOfPlay();
}

void ACSActor::OnCreate()
{
	CSActorShell::OnCreate();
}

void ACSActor::Reclaim()
{
	CSActorShell::Reclaim();
}

void ACSActor::Destroyed()
{
	Super::Destroyed();
}

void ACSActor::BeginDestroy()
{
	Super::BeginDestroy();
	CSActorShell::OnBeginDestroy();
}

void ACSActor::Tick(float _dt)
{
	CSActorShell::Tick(_dt);
	Super::Tick(_dt);
}
