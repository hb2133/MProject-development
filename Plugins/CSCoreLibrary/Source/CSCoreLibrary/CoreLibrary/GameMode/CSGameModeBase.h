// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API ACSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACSGameModeBase();

protected:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
	virtual void PostLogin(APlayerController* NewPlayer) override; 
	virtual void Logout(AController* Exiting) override;
};
