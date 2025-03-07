// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

typedef long long UNIQUEID;

static const int		INVALID_INDEX = -1;
static const long long	INVALID_UNIQUEID = -1;
static const int		MAX_CALCULATOR_COUNT = 10;
static const int		MAX_OPERATION_COUNT = 5;
static const int		MAX_INPUT_COUNT = 5;

static const int		INVALID_CLIENT_SLOT = -1;

#define INVALID_ARRAY_INDEX (-1)
#define INVALID_VALUES (-1)
#define PLAY_MAP_NAME (FName("PlayDemoMap"))

#if !UE_BUILD_SHIPPING
#define CSPROJECT_DEBUG
#endif

#if WITH_EDITOR
	#define CS_LOGIN_EDITOR
#else
	#define CS_LOGIN_REAL
#endif

#if PLATFORM_WINDOWS
#elif PLATFORM_ANDROID
#elif PLATFORM_IOS
#endif