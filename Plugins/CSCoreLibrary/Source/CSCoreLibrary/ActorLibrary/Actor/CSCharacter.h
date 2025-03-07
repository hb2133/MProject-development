// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActorLibrary/Actor/Shell/CSActorShell.h"
#include "Components/TimelineComponent.h"
#include "Engine/EngineTypes.h"
#include "CSCharacter.generated.h"

DECLARE_EVENT(ACSCharacter, FCSLandedDelegate);

class USkeletalMeshComponent;
class UCSWidgetComponent;

UCLASS()
class CSCORELIBRARY_API ACSCharacter : public ACharacter, public CSActorShell
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* CurveFloat_Scale;

	UFUNCTION()
		void TimeLineProgress_Scale(float scaleValue);

public:
	ACSCharacter();


	
protected:
	virtual void PostActorCreated() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type _eReason) override;

	virtual void OnCreate() override;

	virtual void Reclaim() override;
	virtual void Destroyed() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float _dt) override;
	virtual void Landed(const FHitResult& Hit) override;

	virtual void SetChatMessage(const FString& strMessage);
public:
	virtual void SetActorHiddenInGame(bool bNewHidden) override;
	const FVector& GetMoveDirection() { return m_vMove; }
	EMovementMode GetMovementMode();

	virtual void SetHideSpeechBubble();
protected:
	FCSLandedDelegate LandedDelegate;

public:
	FCSLandedDelegate& OnLandedDelegate() { return LandedDelegate; }
	FTimeline& GetScaleCurveTimeline() {return ScaleCurveTimeline; };
protected:
	FVector m_vMove = FVector::ZeroVector;
	bool		m_prevSendMovePacket;
	FTimeline ScaleCurveTimeline;
};
