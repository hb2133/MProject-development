// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CSWidgetUtils.generated.h"

UENUM(BlueprintType)
enum class ESelectTypeEnum : uint8
{
	None	UMETA(DisplayName = "SelectType_None"),
	Single	UMETA(DisplayName = "SelectType_Single"),
	Multi	UMETA(DisplayName = "SelectType_Multi"),
};

UENUM(BlueprintType)
enum class ESlotParentTypeEnum : uint8
{
	Parent_Normal			UMETA(DisplayName = "SlotParent Normal"),
	Parent_WidgetInterface	UMETA(DisplayName = "SlotParent Widget Interface"),
	Max
};

UCLASS()
class CSCORELIBRARY_API UCSWidgetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EBackBtnType : uint8
{
	Hide UMETA(DisplayName = "BackBtnType_Hide"),
	Max UMETA(DisplayName = "MAX"),
	
};
