// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Utilities/CSDeclareEnumMap.h"

//:: Enum
CSEnumStruct nResourceType
{
	CSEnumDefault
	{
		General,
		Blueprint,
		UClass, // ex) AnimBlueprint
		Max
	};

	CSEnumMapRegist
	{
		InsertMap(General, "General");
		InsertMap(Blueprint, "Blueprint");
		InsertMap(UClass, "UClass");
	}
}

CSEnumStruct nAssetType
{
	CSEnumDefault
	{
		AnimSequence,   //:: 애님시퀀스
		AnimMontage,	//:: 애님몽타주
		BlendSpace,     //:: 블렌드 스페이스
		AnimBlueprint,  //:: 애님 블루프린트

		StaticMesh,		//:: 스테틱 메쉬
		SkeletalMesh,	//:: 스켈레탈 메쉬

		PaperSprite,    //:: 스프라이트 (텍스쳐)
		Texture2D,
		SoundCue,		//:: 사운드큐

		MaterialInstance,
		
		Max,

		AnimAssetBeg = AnimBlueprint,
		AnimAssetEnd = BlendSpace,

		MeshAssetBeg = StaticMesh,
		MeshAssetEnd = SkeletalMesh,

		TextureAssetBeg = PaperSprite,
		TextureAssetEnd = Texture2D,

		SoundAssetBeg = SoundCue,
		SoundAssetEnd = SoundCue,

		MaterialAssetBeg = MaterialInstance,
		MaterialAssetEnd = MaterialInstance,
	};

	CSEnumMapRegist
	{
		InsertMap(AnimSequence, "AnimSequence");
		InsertMap(AnimMontage, "AnimMontage");
		InsertMap(BlendSpace, "BlendSpace");
		InsertMap(AnimBlueprint, "AnimBlueprint");

		InsertMap(StaticMesh, "StaticMesh");
		InsertMap(SkeletalMesh, "SkeletalMesh");

		InsertMap(PaperSprite, "PaperSprite");
		InsertMap(Texture2D, "Texture2D");
		InsertMap(SoundCue, "SoundCue");
		InsertMap(MaterialInstance,"MaterialInstance");
	}
}


//:: Struct

struct SAssetInfo
{
	FName strPath = FName("");
	FName strFileName = FName("");
	FName strResourceKey = FName(""); //:: 리소스 테이블 연동시 사용
	nAssetType::en eAssetType = nAssetType::Max;
	bool bValidInfo = false;

	SAssetInfo() {}
	SAssetInfo(const FName& _strPath, const FName& _strFileName)
		: strPath(_strPath), strFileName(_strFileName) {}
	SAssetInfo(const FName& _strPath, const FName& _strFileName, const nAssetType::en& _eAssetType)
		: strPath(_strPath), strFileName(_strFileName), eAssetType(_eAssetType) {}
};