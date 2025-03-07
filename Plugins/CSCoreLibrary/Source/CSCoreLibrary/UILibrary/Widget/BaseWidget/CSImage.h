// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "CSImage.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSImage : public UImage
{
	GENERATED_BODY()
public:
	virtual void SetBrushFromTextureName(FString& strTextureName);
	virtual void SetBrushFromSpriteName(const FString& strSpriteName, bool bMatchSize = false);
	
};
