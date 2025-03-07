#include "MProject_Drigger_AnimInstance.h"

#include "Kismet/GameplayStatics.h"
#include "MProject/PlayerCharacter/MProject_Chawracter_Drigger.h"

UMProject_Drigger_AnimInstance::UMProject_Drigger_AnimInstance() : MovementState(EMovementState::Idle)
{
	
}

void UMProject_Drigger_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterRef && IsValid(TryGetPawnOwner()))
	{
		CharacterRef = Cast<AMProject_Chawracter_Drigger>(TryGetPawnOwner());
	}

	if (CharacterRef)
	{
		if(CharacterRef->State == EState::Digging)
		{
			MovementState = EMovementState::Digging;
		}
		else if(CharacterRef->State == EState::Pick)
		{
			MovementState = EMovementState::Pick;
		}
		else if(CharacterRef->State == EState::Drill)
		{
			MovementState = EMovementState::Drill;
		}
		else
		{
			MovementState = EMovementState::Idle;
		}
	}
}
