// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorLibrary/Define/CSActorCommon.h"
#include "CSLevelPlacedActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSCORELIBRARY_API UCSLevelPlacedActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, DisplayName = "Append Builer Type", Category = "CSLevelPlacedActorComponent")
	EActorBuilderType eBuilderType;

	UPROPERTY(EditAnywhere, DisplayName = "Actor Table Tid", Category = "CSLevelPlacedActorComponent")
	FName strActorTid;

public:	
	UCSLevelPlacedActorComponent();

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
