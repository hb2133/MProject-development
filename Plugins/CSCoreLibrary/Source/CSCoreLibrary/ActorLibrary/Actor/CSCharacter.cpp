// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorLibrary/Actor/CSCharacter.h"
#include "CoreLibrary/Define/CSClientDefine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "ActorLibrary/Actor/Component/ActorComponent/CSWidgetComponent.h"

void ACSCharacter::TimeLineProgress_Scale(float scaleValue)
{
	FVector vScale = FMath::Lerp(FVector(0.f),FVector(1.f),scaleValue);
	this->SetActorScale3D(vScale);
}

ACSCharacter::ACSCharacter()
	: CSActorShell(this)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


}

void ACSCharacter::PostActorCreated()
{
	Super::PostActorCreated();
}

void ACSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACSCharacter::BeginPlay()
{
	Super::BeginPlay();
	CSActorShell::OnBeginPlay();

	if(CurveFloat_Scale)
	{
		FOnTimelineFloat OnTimelineProgress_Scale;
		OnTimelineProgress_Scale.BindUFunction(this,FName("TimeLineProgress_Scale"));
		ScaleCurveTimeline.AddInterpFloat(CurveFloat_Scale,OnTimelineProgress_Scale);		
	}
	
}
void ACSCharacter::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);
	if(bNewHidden == false)
	{
		if(CurveFloat_Scale)
		{
			FVector vLoc = GetActorLocation();			
			//vLoc.Z += SPAWN_LOCATION_Z_VALUE;
			SetActorLocation(vLoc);
			ScaleCurveTimeline.PlayFromStart();
		}	
	}
	
}
void ACSCharacter::EndPlay(EEndPlayReason::Type _eReason)
{
	Super::EndPlay(_eReason);
	CSActorShell::OnEndOfPlay();
}

void ACSCharacter::OnCreate()
{
	CSActorShell::OnCreate();
}

void ACSCharacter::Reclaim()
{
	m_vMove = FVector::ZeroVector;

	CSActorShell::Reclaim();
}

void ACSCharacter::Destroyed()
{
	Super::Destroyed();
}

void ACSCharacter::BeginDestroy()
{
	Super::BeginDestroy();
	CSActorShell::OnBeginDestroy();
}

void ACSCharacter::Tick(float _dt)
{
	CSActorShell::Tick(_dt);
	Super::Tick(_dt);

	if(CurveFloat_Scale)
	{
		ScaleCurveTimeline.TickTimeline(_dt);
	}
}

void ACSCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	LandedDelegate.Broadcast();
}

void ACSCharacter::SetChatMessage(const FString& strMessage)
{

}

void ACSCharacter::SetHideSpeechBubble()
{

	
}

