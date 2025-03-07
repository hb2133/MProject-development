// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"

//:: Enum

CSEnumStruct nUIPanelType
{
	CSEnumDefault
	{
		Main,
		Lobby,
		InApp,
		GameRunning,
		GameDigging,
		Customize,
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(Main, "Main");
		InsertMap(Lobby, "Lobby");
		InsertMap(InApp, "InApp");
		InsertMap(GameRunning, "GameRunning");
		InsertMap(GameDigging, "GameDigging");
		InsertMap(Customize, "Customize");
	}
}

CSEnumStruct nBackBtnActionType
{
	CSEnumDefault
	{
		NoAction,
		OnClose,
		OnClosePopup,
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(NoAction, "NoAction");
		InsertMap(OnClose, "OnClose");
	}
}


//:: Struct

struct SPanelTypeInfo
{
	nUIPanelType::en ePanelType;
	FName strUIRecordKey; 
	int nUILayer;

	SPanelTypeInfo()
	{
		ePanelType = nUIPanelType::en::Max;
		strUIRecordKey = FName("");
		nUILayer = 0;
	}

	SPanelTypeInfo(nUIPanelType::en _ePanelType, FName _strUIRecordKey, int _nUILayer = 0)
	{
		ePanelType = _ePanelType;
		strUIRecordKey = _strUIRecordKey;
		nUILayer = _nUILayer;
	}
};

struct FChildZOrder
{
	int32 ChildIndex;
	float ZOrder;
};

struct FSortSlotsByZOrder
{
	FORCEINLINE bool operator()( const FChildZOrder& A, const FChildZOrder& B ) const
	{
		return A.ZOrder == B.ZOrder ? A.ChildIndex < B.ChildIndex : A.ZOrder < B.ZOrder;
	}
};

#define BIND_BUTTON_EVENT(Button, Function) \
{ \
if(Button) Button->OnClicked.AddDynamic(this, Function); \
}

#define UNBIND_BUTTON_EVENT_ALL(Button) \
{ \
if(Button) Button->OnClicked.RemoveAll(this);  \
}

#define BIND_RADIOGROUP_EVENT(RadioGroup, Function) \
{ \
if(RadioGroup) RadioGroup->OnSelectedIndexChanged.AddDynamic(this, Function); \
}

#define UNBIND_RADIOGROUP_EVENT_ALL(RadioGroup) \
{ \
if(RadioGroup) RadioGroup->OnSelectedIndexChanged.RemoveAll(this); \
}

#define CS_IF_NULLPTR_RET(Item) \
{ \
if (nullptr == Item) return; \
}

#define CS_IF_NULLPTR_CONTINUE(Item) \
{ \
if (!Item) continue; \
}

#define CS_IF_NOT_RET(Item) \
{ \
if (!Item) return; \
}
