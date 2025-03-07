// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectAnimInstance.h"

#include "MProject/PlayerCharacter/MProject_Character.h"

UMProjectAnimInstance::UMProjectAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UMProjectAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterRef)
	{
		APawn* Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			CharacterRef = Cast<AMProject_Character>(Pawn);
		}
	}

	if (CharacterRef)
	{
		CurrentPawnSpeed = CharacterRef->CurrentSpeed;
		//UE_LOG(LogTemp, Log, TEXT("CurrentPawnSpeed: %f"), CurrentPawnSpeed);
	}
	else
	{
		CurrentPawnSpeed = 0.0f;
	}
}
