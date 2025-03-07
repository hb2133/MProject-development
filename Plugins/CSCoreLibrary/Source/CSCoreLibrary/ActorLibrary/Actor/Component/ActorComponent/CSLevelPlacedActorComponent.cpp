// Fill out your copyright notice in the Description page of Project Settings.


#include "CSLevelPlacedActorComponent.h"
#include "ActorLibrary/FunctionLibrary/CSActorFunctionLibrary.h"
#include "ActorLibrary/Manager/CSActorMgr.h"

// Sets default values for this component's properties
UCSLevelPlacedActorComponent::UCSLevelPlacedActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UCSLevelPlacedActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (eBuilderType != EActorBuilderType::None)
	{
		if (CSActorShell* _pOwnerShell = UCSActorFunctionLibrary::ConvertShell(GetOwner()))
		{
			if (g_ActorMgrValid)
				g_ActorMgr->AppendShellBuilder(eBuilderType, _pOwnerShell, strActorTid);
		}
	}
}

void UCSLevelPlacedActorComponent::BeginDestroy()
{
	Super::BeginDestroy();
}

