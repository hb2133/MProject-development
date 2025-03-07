// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"
#include "CSActorCommon.generated.h"

//:: Enum

UENUM(BlueprintType)
enum class EActorBuilderType : uint8
{
	None						UMETA(DisplayName = "None"),
	CSPlayerBuilder				UMETA(DisplayName = "CSPlayerBuilder"),
	CSNPCBuilder				UMETA(DisplayName = "CSNPCBuilder"),
	CSInteractionObjectBuilder	UMETA(DisplayName = "CSInteractionObjectBuilder"),
	CSPortalBuilder				UMETA(DisplayName = "CSPortalBuilder"),
	CSSoundBuilder				UMETA(DisplayName = "CSSoundBuilder"),
};

enum class EShellComponentType
{
	eNoneComp = -1,
	eInteractionComp,
	eMobileComp,
	eGrab,
	Max
};

const float SPAWN_LOCATION_Z_VALUE = 100.f;