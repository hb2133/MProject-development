// Fill out your copyright notice in the Description page of Project Settings.


#include "MProject_EndDrigger.h"

#include "ActorLibrary/Actor/Component/ActorComponent/CSStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MProject/PlayerCharacter/MProject_Chawracter_Drigger.h"

void UMProject_EndDrigger::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AMProject_Chawracter_Drigger* PlayerCharacter = Cast<AMProject_Chawracter_Drigger>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			switch (PlayerCharacter->State)
			{
			case EState::Digging:
				PlayerCharacter->TraceForObjects("Block1");
				break;
			case EState::Pick:
				PlayerCharacter->TraceForObjects("Block2");
				break;
			case EState::Drill:
				PlayerCharacter->TraceForObjects("Block3");
				break;
				default:
					break;
			}
			PlayerCharacter->StaticMeshComponent->SetHiddenInGame(true);
			PlayerCharacter->State = EState::Idle;
		}
	}
}
