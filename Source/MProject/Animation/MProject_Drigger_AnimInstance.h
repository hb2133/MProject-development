#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Animation/CSAnimInstance.h"
#include "MProject_Drigger_AnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Digging UMETA(DisplayName = "Digging"),
	Pick UMETA(DisplayName = "Pick"),
	Drill UMETA(DisplayName = "Drill")
};

class AMProject_Chawracter_Drigger;
UCLASS()
class MPROJECT_API UMProject_Drigger_AnimInstance : public UCSAnimInstance
{
	GENERATED_BODY()

	UMProject_Drigger_AnimInstance();
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
	EMovementState MovementState;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool m_bPick;

	UPROPERTY()
	AMProject_Chawracter_Drigger* CharacterRef;
	
};
