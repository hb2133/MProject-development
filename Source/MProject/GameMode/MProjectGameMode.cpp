// Copyright Epic Games, Inc. All Rights Reserved.

#include "MProjectGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMProjectGameMode::AMProjectGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Actor/MProject_Character_BP.MProject_Character_BP_C"));
	if (PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
}
