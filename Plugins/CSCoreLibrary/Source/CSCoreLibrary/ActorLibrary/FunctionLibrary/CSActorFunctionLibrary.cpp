// Fill out your copyright notice in the Description page of Project Settings.


#include "CSActorFunctionLibrary.h"
#include "GameFramework/Actor.h"

#include "ActorLibrary/Actor/Shell/CSActorShell.h"
#include "ActorLibrary/Actor/CSCharacter.h"
#include "ActorLibrary/Actor/CSPawn.h"
#include "ActorLibrary/Actor/CSActor.h"

CSActorShell* UCSActorFunctionLibrary::ConvertShell(AActor* _pActor)
{
	CSActorShell* _pShell = ::Cast<ACSCharacter>(_pActor);

	if (_pShell == nullptr)
		_pShell = ::Cast<ACSActor>(_pActor);
	if (_pShell == nullptr)
		_pShell = ::Cast<ACSPawn>(_pActor);

	return _pShell;
}
