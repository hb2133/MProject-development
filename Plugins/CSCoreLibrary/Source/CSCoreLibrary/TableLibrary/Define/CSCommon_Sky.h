// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"


//:: Enum

CSEnumStruct nParameterType
{
	CSEnumDefault
	{
		Scalar,
		Vector,
		Texture,
		Max,
	};

	CSEnumMapRegist
	{
		InsertMap(Texture, "Texture");
		InsertMap(Scalar, "Scalar");
		InsertMap(Vector, "Vector");
	}
}

CSEnumStruct nWeatherType
{
	CSEnumDefault
	{
		Skies,
		Rain,
		Snow,
		Max,
	};

	CSEnumMapRegist
	{
		InsertMap(Skies, "Skies");
		InsertMap(Rain, "Rain");
		InsertMap(Snow, "Snow");
	}
}


