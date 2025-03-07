// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CSHUD.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API ACSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACSHUD() {}

public:
	virtual void BeginPlay() override;
	virtual void CreateWidgetPanels() {};

};
