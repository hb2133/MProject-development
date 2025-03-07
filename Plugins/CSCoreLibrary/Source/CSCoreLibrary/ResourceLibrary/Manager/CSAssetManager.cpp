// Fill out your copyright notice in the Description page of Project Settings.

#include "CSAssetManager.h"
#include "CoreLibrary/Manager/CSFileManager.h"
#include "ResourceLibrary/DataTable/DataManager/CSAnimResourceRecordMgr.h"
#include "ResourceLibrary/DataTable/DataManager/CSModelResourceRecordMgr.h"
#include "ResourceLibrary/DataTable/DataManager/CSSpriteResourceRecordMgr.h"
#include "ResourceLibrary/DataTable/DataRecord/CSBaseResourceRecord.h"
#include "PaperSprite.h"
#include "Animation/BlendSpace.h"
#include "ResourceLibrary/DataTable/DataManager/CSMaterialInstanceRecordMgr.h"
#include "ResourceLibrary/DataTable/DataManager/CSSoundResourceRecordMgr.h"
#include "Sound/SoundCue.h"
#include "TableLibrary/DataTable/DataManager/CSSkyRecordMgr.h"

void UCSAssetManager::StartInitialLoading()
{
	this->InitPrimaryScanClass();
	this->LoadResourceTable();
	UE_LOG(LogTemp,Warning,TEXT("TESTCHECK2"));
	this->ScanPathFromResourceRecord_Debug(g_ModelResourceMgr->GetAllRecord_SpecificType<CSBaseResourceRecord>());
	this->ScanPathFromResourceRecord(g_AnimResourceMgr->GetAllRecord_SpecificType<CSBaseResourceRecord>());
	this->ScanPathFromResourceRecord(g_SpriteResourceMgr->GetAllRecord_SpecificType<CSBaseResourceRecord>());
	this->ScanPathFromResourceRecord(g_SoundResourceMgr->GetAllRecord_SpecificType<CSBaseResourceRecord>());
	this->ScanPathFromResourceRecord(g_MaterialInstanceResourceMgr->GetAllRecord_SpecificType<CSBaseResourceRecord>());
	
	Super::StartInitialLoading();
}

void UCSAssetManager::BeginDestroy()
{
	this->ReleaseResourceTable();

	m_PrimaryScanClass.Empty();
	m_LoadedUClass.Empty();

	Super::BeginDestroy();
}

void UCSAssetManager::UnloadAsset(const nAssetType::en _eAssetType, const FName& _strAssetKey)
{
	FPrimaryAssetId _PrimaryAssetId(nAssetType::GetFName(_eAssetType, false), _strAssetKey);
	UAssetManager::UnloadPrimaryAsset(_PrimaryAssetId);
	//수정했습니다.
	FSoftObjectPath _UnloadRef = UAssetManager::GetPrimaryAssetPath(_PrimaryAssetId);
	FStreamableManager& _StreamableManager = UAssetManager::GetStreamableManager();

	_StreamableManager.Unload(_UnloadRef);
}

UClass* UCSAssetManager::FindPrimaryScanClass(const nAssetType::en& _eAssetType)
{
	if (_eAssetType == nAssetType::Max)
	{
		UE_LOG(LogTemp, Log, TEXT("FindAssetType Is Max ( InValid )"));
		return nullptr;
	}

	FName _strPrimaryAssetType = nAssetType::GetFName(_eAssetType, false);
	return m_PrimaryScanClass.FindRef(FPrimaryAssetType(_strPrimaryAssetType));
}

UClass* UCSAssetManager::FindUClassFromFile(const FName& _strFileName)
{
	UClass* _pSearchClass = nullptr;
	//if (m_LoadedUClass.Contains(_strFileName))
	//{
	//	_pSearchClass = m_LoadedUClass.FindRef(_strFileName);
	//}
	//else
	//{
	//	_pSearchClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass, _strFileName);
	//	if (_pSearchClass)
	//		m_LoadedUClass.Add(_strFileName, _pSearchClass);
	//}
	return _pSearchClass;
}

void UCSAssetManager::InitPrimaryScanClass()
{
	m_PrimaryScanClass.Empty();
	m_PrimaryScanClass.Add(FPrimaryAssetType("AnimSequence"), UAnimSequence::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("AnimMontage"), UAnimMontage::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("BlendSpace"), UBlendSpace::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("StaticMesh"), UStaticMesh::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("SkeletalMesh"), USkeletalMesh::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("PaperSprite"), UPaperSprite::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("Texture2D"), UTexture2D::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("SoundCue"),USoundCue::StaticClass());
	m_PrimaryScanClass.Add(FPrimaryAssetType("MaterialInstance"),UMaterialInstance::StaticClass());
}

void UCSAssetManager::LoadResourceTable()
{
	g_FileMgr->Load();
	g_ModelResourceMgr->Load();
	g_AnimResourceMgr->Load();
	g_SpriteResourceMgr->Load();
	g_SoundResourceMgr->Load();
	g_SkyRecordMgr->Load();
	g_MaterialInstanceResourceMgr->Load();
}

void UCSAssetManager::ReleaseResourceTable()
{
	g_FileMgr->Release();
	g_ModelResourceMgr->Release();
	g_AnimResourceMgr->Release();
	g_SpriteResourceMgr->Release();
	g_SoundResourceMgr->Release();
	g_SkyRecordMgr->Release();
	g_MaterialInstanceResourceMgr->Release();
}

void UCSAssetManager::ScanPathFromResourceRecord_Debug(TArray<CSBaseResourceRecord*> _arrBaseResourceRecords)
{
	for (auto iter : _arrBaseResourceRecords)
	{
		FString _strAssetPath = FString("");
		if (g_FileMgr->GetAssetPath(nResourceType::General, iter->_strAssetFileName, _strAssetPath))
		{
			FName _strPrimaryAssetType = nAssetType::GetFName(iter->_eAssetType, false);
			if (UClass* _pClass = m_PrimaryScanClass.FindRef(_strPrimaryAssetType))
			{
				UE_LOG(LogTemp, Log, TEXT("SynchronousLoadAsset strAssetKey:%s,%s"), *(_strAssetPath),*(_strPrimaryAssetType.ToString()));
				ScanPathForPrimaryAssets(FPrimaryAssetType(_strPrimaryAssetType), _strAssetPath, _pClass, false);
			}
		}
	}
}


void UCSAssetManager::ScanPathFromResourceRecord(TArray<CSBaseResourceRecord*> _arrBaseResourceRecords)
{
	for (auto iter : _arrBaseResourceRecords)
	{
		FString _strAssetPath = FString("");
		if (g_FileMgr->GetAssetPath(nResourceType::General, iter->_strAssetFileName, _strAssetPath))
		{
			FName _strPrimaryAssetType = nAssetType::GetFName(iter->_eAssetType, false);
			if (UClass* _pClass = m_PrimaryScanClass.FindRef(_strPrimaryAssetType))
			{
				ScanPathForPrimaryAssets(FPrimaryAssetType(_strPrimaryAssetType), _strAssetPath, _pClass, false);
			}
		}
	}
}

FPrimaryAssetId UCSAssetManager::ExtractPrimaryAssetIdFromData(const FAssetData& AssetData,
	FPrimaryAssetType SuggestedType) const
{
	//return Super::ExtractPrimaryAssetIdFromData(AssetData, SuggestedType);
	
	return FPrimaryAssetId(SuggestedType, SuggestedType == MapType ? AssetData.PackageName : AssetData.AssetName);
}
