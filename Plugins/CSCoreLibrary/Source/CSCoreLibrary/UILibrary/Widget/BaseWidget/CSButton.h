// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CSButton.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSButton : public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString m_strBtnSound;

	UPROPERTY(EditAnywhere)
	float m_fPlayTime = 0.f;
public:
	virtual void SynchronizeProperties() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	UFUNCTION() void OnClick_Sound();



};
