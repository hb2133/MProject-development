#pragma once

#include "CoreMinimal.h"
#include "MProject/MProjectCharacter.h"
#include "MProject_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class MPROJECT_API AMProject_Character : public AMProjectCharacter
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHPChanged, int32, NewHP);
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPlayerHPChanged OnPlayerHPChanged;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChanged, int32, NewScore);
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPlayerScoreChanged OnPlayerScoreChanged;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerCleared);
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPlayerCleared OnPlayerClear;
	
private:
	// 마지막으로 눌린 버튼을 추적
	enum class EButtonType { None, Red, Green, Blue };
	EButtonType LastButtonPressed;
	
public:
	AMProject_Character();

	// Public Functions
	void IncreaseSpeed();
	void TESTIncreaseSpeed();
	void SetButtonPressed(bool bIsRedButtonPressed, bool bIsGreenButtonPressed, bool bIsBlueButtonPressed);
	float CurrentSpeed;
	bool m_bCHEATMODE;

	void SetGameClear(bool ClearState) { m_bGameClear = ClearState; }
	bool GetGameClear() { return m_bGameClear; }
	void SetPlayerHP(int32 PlayerHP) { m_iPlayerHP = PlayerHP; }
	int32 GetPlayerHP() { return m_iPlayerHP; }
	void SetWarningCount(int32 WarningCount) { m_iWarningCount = WarningCount; }
	int32 GetWarningCount() { return m_iWarningCount; }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Spline and Movement Variables
	UPROPERTY(EditAnywhere, Category = "Spline")
	class AMProjectActor_Spline* TargetSplineActor;

	float SplineDistance;
	float ClickDistance;
	float MaxSpeed;
	float SpeedDecay;

	// Cheat Mode Speed Multiplier
	float SpeedMultiplier;

	// Lap Tracking
	int32 LapCount;
	int32 TotalLaps;

	// Button States
	bool bRedButtonPressed;
	bool bGreenButtonPressed;
	bool bBlueButtonPressed;

	bool m_bGameClear;
	int32 m_iPlayerHP;
	int32 m_iWarningCount = 0;

	// Timer Handle for Button Cooldown
	FTimerHandle ButtonCooldownTimerHandle;

	// Private Helper Functions
	void ResetButtonState();
	void OnLapComplete();
};
