// Fill out your copyright notice in the Description page of Project Settings.


#include "MProject_Chawracter_Drigger.h"

#include "ActorLibrary/Actor/Component/ActorComponent/CSStaticMeshComponent.h"
#include "ActorLibrary/Actor/Component/ActorComponent/CSWidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "MProject/Actor/MProjectActor_Block.h"
#include "MProject/UI/MProjectWidget_DriggerCount.h"

AMProject_Chawracter_Drigger::AMProject_Chawracter_Drigger()
{
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UCSWidgetComponent>("WidgetComponent");
	if(WidgetComponent)
	{
		WidgetComponent->SetupAttachment(RootComponent);
	}
	StaticMeshComponent = CreateDefaultSubobject<UCSStaticMeshComponent>("WP_StaticMeshComponent");
	if(StaticMeshComponent)
	{
		StaticMeshComponent->SetupAttachment(RootComponent);
	}


	PlayerHP = 3;
	m_iDriggerMeter = 0;
	m_iDriggernumScore = 0;
	m_iWarningCount = 0;
}

void AMProject_Chawracter_Drigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (FollowCamera)
	{
		FollowCamera->SetRelativeLocation(FVector(800.0f, 0.0f, 0.0f));
		FollowCamera->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}

}

void AMProject_Chawracter_Drigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceLine();
}

void AMProject_Chawracter_Drigger::TraceLine()
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation;
	EndLocation.Z -= 220.0f;

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("TraceLine")), true, this);
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1.0f, 0, 1.0f);

	if (bHit && HitResult.GetActor())
	{
		Block = Cast<AMProjectActor_Block>(HitResult.GetActor());
		if (Block)
		{
			BlockHPCount = Block->GetBlockHealth();
		}
		
		// 감지된 객체의 태그를 확인
		if (HitResult.GetActor()->ActorHasTag("Block1"))
		{
			if(WidgetComponent)
			{
		
				if(UMProjectWidget_DriggerCount* pSlot = Cast<UMProjectWidget_DriggerCount>(WidgetComponent->GetWidget()))
				{
					if(Block && BlockHPCount)
					{
						pSlot->SetBlockOneCount(BlockHPCount);			
					}
				}
			}
		}
		else if (HitResult.GetActor()->ActorHasTag("Block2"))
		{
			if(WidgetComponent)
			{
		
				if(UMProjectWidget_DriggerCount* pSlot = Cast<UMProjectWidget_DriggerCount>(WidgetComponent->GetWidget()))
				{
					if(Block && BlockHPCount)
					{
						pSlot->SetBlockTwoCount(BlockHPCount);
					}
				}
			}
		}
		else if (HitResult.GetActor()->ActorHasTag("Block3"))
		{
			if(WidgetComponent)
			{
		
				if(UMProjectWidget_DriggerCount* pSlot = Cast<UMProjectWidget_DriggerCount>(WidgetComponent->GetWidget()))
				{
					if(Block && BlockHPCount)
					{
						pSlot->SetBlockThreeCount(BlockHPCount);
					}
				}
			}
		}
	}
}


void AMProject_Chawracter_Drigger::TraceForObjects(FString TagName)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation;
	EndLocation.Z -= 200.0f;

	TArray<FVector> Offsets =
		{ FVector(0.0f, 0.0f, 0.0f) };

	for (const FVector& Offset : Offsets)
	{
		FVector TraceStart = StartLocation + Offset;
		FVector TraceEnd = EndLocation + Offset;

		FHitResult HitResult;
		FCollisionQueryParams TraceParams(FName(TEXT("TraceForObjects")), true, this);
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 1.0f);
		
		if (bHit && HitResult.GetActor())
		{
			if (HitResult.GetActor()->ActorHasTag(FName(TagName)))
			{
				UE_LOG(LogTemp, Log, TEXT("Object with tag '%s' detected at location: %s"), *TagName, *HitResult.Location.ToString());
				Block = Cast<AMProjectActor_Block>(HitResult.GetActor());
				if (Block)
				{
					Block->ReduceHealth();
					m_iDriggernumScore += 1;
					if(Block->GetBlockHealth() == 0)
					{
						m_iDriggerMeter += 1;
						OnDriggerPlayerScoreChanged.Broadcast(m_iDriggerMeter);
					}
				}
			}
			else
			{
				// 감지된 액터의 태그가 다를 때 로그 출력
				LogMismatchedTag(HitResult.GetActor(), TagName);
			}
		}
	}
}

void AMProject_Chawracter_Drigger::LogMismatchedTag(AActor* DetectedActor, FString ExpectedTag)
{
	if (PlayerHP > 0)
	{
		PlayerHP -= 1;
		OnDriggerPlayerHPChanged.Broadcast(PlayerHP);
		m_iWarningCount += 1;
		UE_LOG(LogTemp, Log, TEXT("Player HP updated to: %d"), PlayerHP);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player HP is already zero or less."));
	}

	// 감지된 액터의 첫 번째 태그 가져오기 (여러 태그가 있을 수 있음)
	FName DetectedTag = DetectedActor->Tags.Num() > 0 ? DetectedActor->Tags[0] : FName("None");
	UE_LOG(LogTemp, Warning, TEXT("Tag mismatch: Expected '%s', but detected '%s' on actor '%s'"), *ExpectedTag, *DetectedTag.ToString(), *DetectedActor->GetName());
}