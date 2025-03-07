// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "CSSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Rendering, Common), hidecategories = Object, config = Engine, editinlinenew, meta = (BlueprintSpawnableComponent))
class CSCORELIBRARY_API UCSSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	virtual void InitializeComponent() override;
};
