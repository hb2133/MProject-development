// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Animation/CSAnimInstance.h"
#include "MProjectAnimInstance.generated.h"

class AMProject_Character;
UCLASS()
class MPROJECT_API UMProjectAnimInstance : public UCSAnimInstance
{
	GENERATED_BODY()

	UMProjectAnimInstance();
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
	UPROPERTY()
	AMProject_Character* CharacterRef;
};
