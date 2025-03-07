// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorLibrary/Controller/CSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "UILibrary/Manager/CSUIMgr.h"

void ACSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("BackButton", IE_Pressed, this, &ACSPlayerController::OnClickBackButton);
}

void ACSPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACSPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ACSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ACSPlayerController::BeginDestroy()
{
	Super::BeginDestroy();
}

void ACSPlayerController::OnClickBackButton()
{
#if(UE_EDITOR || PLATFORM_ANDROID)
	if(g_UIMgrValid) 
		g_UIMgr->OnExeBackBtn();
#endif
}
