// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"


CSEnumStruct nGameMsgType
{
	CSEnumDefault
	{
		None,
		MsgPopup,
		DoubleMsgPopup,
		ResultMsgPopup,
		GoogleMsgPopup,
		GoogleResultMsgPopup,
		Max,
	};

	CSEnumMapRegist
	{
		InsertMap(MsgPopup, "MsgPopup");
		InsertMap(DoubleMsgPopup, "DoubleMsgPopup");
		InsertMap(ResultMsgPopup, "ResultMsgPopup");
		InsertMap(GoogleMsgPopup, "GoogleMsgPopup");
		InsertMap(GoogleResultMsgPopup, "GoogleResultMsgPopup");
	}
}
namespace nMsgLayerType
{
	CSEnumDefault
	{
		None,
		Common,
		Normal,
		High,
		Play,
		Max,
	};

	CSEnumMapRegist
	{
		InsertMap(Common, "common");
		InsertMap(Normal, "normal");
		InsertMap(High, "high");
		InsertMap(Play, "Play");
	}
}
CSEnumStruct nPopupShowButtonType
{
	CSEnumDefault
	{
		Ok,
		OkCancel,
		Empty,
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(Ok, "Ok");
		InsertMap(OkCancel, "OkCancel");
		InsertMap(Empty, "Empty");
	}
}

UENUM()
namespace EPopupEventID
{
	enum en
	{
		Ok,
		Cancel,
	};
}