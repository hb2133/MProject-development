// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MProject/MProjectCharacter.h"
#include "MProject_Chawracter_Drigger.generated.h"


class UAnimMontage;

UENUM(BlueprintType)
enum class EState : uint8
{
	Idle,
	Digging,
	Pick,
	Drill,
};

class UCSWidgetComponent;
class UMProjectWidget_DriggerCount;
class AMProjectActor_Block;
class UCSStaticMeshComponent;
UCLASS()
class MPROJECT_API AMProject_Chawracter_Drigger : public AMProjectCharacter
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDriggerPlayerHPChanged, int32, HP);
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDriggerPlayerHPChanged OnDriggerPlayerHPChanged;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDriggerPlayerScoreChanged, int32, NewScore);
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDriggerPlayerScoreChanged OnDriggerPlayerScoreChanged;
	
	AMProject_Chawracter_Drigger();

	void TraceForObjects(FString TagName);
	void LogMismatchedTag(AActor* DetectedActor, FString ExpectedTag);
	void TraceLine();

	void SetWarningCount(int32 WarningCount) { m_iWarningCount = WarningCount; }
	int32 GetWarningCount() { return m_iWarningCount; }
	void SetDriggerScoreCount(int32 DriggerScore) { m_iDriggernumScore = DriggerScore; }
	int32 GetDriggerScoreCount() { return m_iDriggernumScore; }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
	EState State;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Animation)
	TObjectPtr<UAnimMontage> Montage;
	UPROPERTY(EditAnywhere)
	UCSWidgetComponent* WidgetComponent;
	UPROPERTY(EditAnywhere)
	UCSStaticMeshComponent* StaticMeshComponent;
	int32 BlockHPCount;

	UPROPERTY()
	AMProjectActor_Block* Block;

	int32 PlayerHP;

	int32 m_iDriggerMeter;
	int32 m_iDriggernumScore;
	int32 m_iWarningCount;
};
