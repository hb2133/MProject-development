// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CSActorFunctionLibrary.generated.h"

class AActor;
class CSActorShell;

UCLASS()
class CSCORELIBRARY_API UCSActorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static CSActorShell* ConvertShell(AActor* _pActor);
};
