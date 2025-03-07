// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "CSWidgetSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSWidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()

public:
	virtual void SetActiveWidgetIndex(int32 Index) override;
	virtual void SetActiveWidget(UWidget* Widget) override;

public:
	void ShowActiveWidgetPanel(bool _bShow);
};
