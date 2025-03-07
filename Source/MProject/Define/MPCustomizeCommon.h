// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"

//Test
// #define INVALID_OBJECT_INDEX -1
//:: Enum

struct ItemInfo
{
	FString strSpriteName;
	FString strCustomType;
	FString strItemType;
	bool bIsWearing;
};

CSEnumStruct nCustomType
{
	CSEnumDefault
	{
		Bag,
		Chest,
		Pants,
		Tool,
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(Bag, "Bag");
		InsertMap(Chest, "Chest");
		InsertMap(Pants, "Pants");
		InsertMap(Tool, "Tool");
	}
}

CSEnumStruct nItemType
{
	CSEnumDefault
	{
		Unique,
		Epic,
		Rear,
		Normal,
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(Unique, "Unique");
		InsertMap(Epic, "Epic");
		InsertMap(Rear, "Rear");
		InsertMap(Normal, "Normal");
	}
}