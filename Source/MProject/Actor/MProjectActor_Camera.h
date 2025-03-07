// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/CSActor.h"
#include "MProjectActor_Camera.generated.h"

class UCameraComponent;
UCLASS()
class MPROJECT_API AMProjectActor_Camera : public ACSActor
{
	GENERATED_BODY()
public:
	AMProjectActor_Camera();
	UPROPERTY(Category=COLLISION_GIZMO, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _dt) override;
};
