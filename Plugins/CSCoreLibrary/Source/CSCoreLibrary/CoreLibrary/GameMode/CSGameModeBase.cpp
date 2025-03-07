// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreLibrary/GameMode/CSGameModeBase.h"

//#include "CoreActor/Controller/CSLecturePlayerController.h"
//#include "CoreActor/GameState/CSLectureGameState.h"
//#include "CoreActor/PlayerState/CSClassPlayerState.h"
//#include "Defines/CSClassDefines.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

ACSGameModeBase::ACSGameModeBase()
{
}

void ACSGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	//const FString ClassRole = UGameplayStatics::ParseOption(Options, CLASS_ROLE_OPTION_NAME);
	//const FString Username = UGameplayStatics::ParseOption(Options, TEXT("Username"));

	//if (auto* GS = GetGameState<ACSLectureGameState>())
	//{
	//	for (const auto* PS : GS->PlayerArray)
	//	{
	//		if (Username.Equals(PS->GetPlayerName()))
	//		{
	//			ErrorMessage = TEXT("이미 같은 이름의 사용자가 존재합니다.");
	//			return;
	//		}
	//	}

	//	if (GS->GetCurrentPlayerNum() < GS->GetMaxPlayerNum())
	//	{
	//		if (ClassRole.Equals(CLASS_ROLE_TEACHER))
	//		{
	//			if (GS->IsTeacherAttended())
	//			{
	//				ErrorMessage = TEXT("다른 선생님이 이미 강의하고 계십니다.");
	//				return;
	//			}

	//			GS->Server_MakeTeacherAttend();
	//		}
	//	}
	//	else
	//	{
	//		ErrorMessage = TEXT("교실에 자리가 없습니다.");
	//	}
	//}


}

FString ACSGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString Result = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	//check(Result != FString(TEXT("PlayerState is null")));

	//const FString Username = UGameplayStatics::ParseOption(Options, TEXT("Username"));
	//const FString ClassRole = UGameplayStatics::ParseOption(Options, CLASS_ROLE_OPTION_NAME);
	//const FString Gender = UGameplayStatics::ParseOption(Options, CLASS_GENDER_OPTION_NAME);

	//UE_LOG(LogTemp, Warning, TEXT("%s Joined - Option: %s, ClassRole: %s, Gender: %s"), *Username, *Options, *ClassRole, *Gender);

	//if (auto* PS = NewPlayerController->GetPlayerState<ACSClassPlayerState>())
	//{
	//	PS->SetPlayerName(Username);

	//	if (ClassRole.Equals(CLASS_ROLE_TEACHER))
	//	{
	//		PS->SetClassRole(EClassRole::Teacher);
	//		PS->SetClassGender(EClassGender::None);
	//	}
	//	else
	//	{
	//		int32 HairIndex = FCString::Atoi(*UGameplayStatics::ParseOption(Options, "HairIndex"));
	//		PS->SetClassRole(EClassRole::Student);
	//		PS->SetHairMatIndex(HairIndex);
	//		// PS->SetClothMatIndex(FMath::RandRange(0, 2));

	//		if (Gender.Equals(CLASS_GENDER_MALE))
	//		{
	//			PS->SetClassGender(EClassGender::Male);
	//		}
	//		else
	//		{
	//			PS->SetClassGender(EClassGender::Female);
	//		}
	//	}

	//	return Result;
	//}

	return TEXT("");
}

void ACSGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//if (auto* GS = GetGameState<ACSLectureGameState>())
	//{

	//	GS->Server_AddPlayerNum();

	//	if (auto* PC = Cast<ACSLecturePlayerController>(NewPlayer))
	//	{
	//		if (PC)
	//		{
	//			Players.Add(PC);
	//		}
	//	}
	//}
}

void ACSGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}
