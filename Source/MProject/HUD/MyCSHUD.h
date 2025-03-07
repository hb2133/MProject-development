// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/HUD/CSHUD.h"
#include "MyCSHUD.generated.h"

/**
 * 
 */
UCLASS()
class MPROJECT_API AMyCSHUD : public ACSHUD
{
	GENERATED_BODY()

	void CreateWidgetPanels();
};
