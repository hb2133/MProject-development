// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"

//:: Enum

CSEnumStruct nFunctionProperty
{
	CSEnumDefault
	{
		Hard,		
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(Hard, "Hard");
	}
}

CSEnumStruct nLocalType
{
	CSEnumDefault
	{
		KO,
		EN,
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(KO, "KO");
		InsertMap(EN,"EN");
	}
}
