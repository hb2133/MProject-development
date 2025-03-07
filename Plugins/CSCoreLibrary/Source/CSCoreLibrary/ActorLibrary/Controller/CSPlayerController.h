// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CSPlayerController.generated.h"
class UInputMappingContext;
class UCSInputConfigData;
/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API ACSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UInputMappingContext* InputMapping;

	UPROPERTY()
	UCSInputConfigData* InputActions;
	
public:
	virtual void SetupInputComponent() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginDestroy() override;

private:
	void OnClickBackButton();
	
};
