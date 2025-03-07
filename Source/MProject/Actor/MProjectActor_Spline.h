// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/CSActor.h"
#include "MProjectActor_Spline.generated.h"

class USplineComponent;
UCLASS()
class MPROJECT_API AMProjectActor_Spline : public ACSActor
{
	GENERATED_BODY()
public:
	AMProjectActor_Spline();
	USplineComponent* SplineComponent;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _dt) override;
};
