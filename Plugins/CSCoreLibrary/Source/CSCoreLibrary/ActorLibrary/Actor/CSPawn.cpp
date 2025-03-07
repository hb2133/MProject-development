// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPawn.h"

ACSPawn::ACSPawn()
	: CSActorShell(this)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ACSPawn::PostActorCreated()
{
	Super::PostActorCreated();
}

void ACSPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACSPawn::BeginPlay()
{
	Super::BeginPlay();
	CSActorShell::OnBeginPlay();
}

void ACSPawn::EndPlay(EEndPlayReason::Type _eReason)
{
	Super::EndPlay(_eReason);
	CSActorShell::OnEndOfPlay();
}

void ACSPawn::OnCreate()
{
	CSActorShell::OnCreate();
}

void ACSPawn::Reclaim()
{
	CSActorShell::Reclaim();
}

void ACSPawn::Destroyed()
{
	Super::Destroyed();
}

void ACSPawn::BeginDestroy()
{
	Super::BeginDestroy();
	CSActorShell::OnBeginDestroy();
}

void ACSPawn::Tick(float _dt)
{
	CSActorShell::Tick(_dt);
	Super::Tick(_dt);
}
