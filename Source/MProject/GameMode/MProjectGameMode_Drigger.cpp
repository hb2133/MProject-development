// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectGameMode_Drigger.h"

AMProjectGameMode_Drigger::AMProjectGameMode_Drigger()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Actor/MProject_Chawracter_Drigger_BP.MProject_Chawracter_Drigger_BP_C"));
	if (PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
}