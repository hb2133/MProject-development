// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"
#include "CSAssetManager.generated.h"

class CSBaseResourceRecord;

UCLASS()
class CSCORELIBRARY_API UCSAssetManager : public UAssetManager
{
	GENERATED_BODY()	

public:
	virtual void StartInitialLoading() override;
	virtual void BeginDestroy() override;

public:
	template<typename T>
	T* SynchronousLoadAsset(const nAssetType::en _eAssetType, const FName& _strAssetKey)
	{
		UE_LOG(LogTemp, Log, TEXT("SynchronousLoadAsset strAssetKey:%s"), *(_strAssetKey.ToString()));
		
		//if (T* _pAsset = FindAsset<T>(_eAssetType, _strAssetKey))
		//	return _pAsset;

		this->SetSynchronousLoad(true);
		
		FPrimaryAssetId _PrimaryAssetId(nAssetType::GetFName(_eAssetType, false), _strAssetKey);
		UAssetManager::LoadPrimaryAsset(_PrimaryAssetId);

		return FindAsset<T>(_eAssetType, _strAssetKey);
	}

	template<typename T>
	T* ASyncLoadAsset(const nAssetType::en _eAssetType, const FName& _strAssetKey)
	{
		//:: 비동기 로드 (구현예정)
		this->SetSynchronousLoad(false);

		return nullptr;
	}

	template<typename T>
	T* FindAsset(const nAssetType::en _eAssetType, const FName& _strAssetKey)
	{
		return this->FindAsset<T>(nAssetType::GetFName(_eAssetType, false), _strAssetKey);
	}

	template<typename T>
	T* FindAsset(const FName _strAssetType, const FName& _strAssetKey)
	{
		if (_strAssetKey.IsNone())
			return nullptr;

		FPrimaryAssetId _PrimaryAssetId(_strAssetType, _strAssetKey);
		T* _pAsset = UAssetManager::GetPrimaryAssetObject<T>(_PrimaryAssetId);
		if (_pAsset == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Can't Find Asset %s"), *(_strAssetKey.ToString()));
		}
		return _pAsset;
	}
	void UnloadAsset(const nAssetType::en _eAssetType, const FName& _strAssetKey);
	UClass* FindPrimaryScanClass(const nAssetType::en& _eAssetType);
	UClass* FindUClassFromFile(const FName& _strFileName);

private:
	void SetSynchronousLoad(bool _bSynchronous) { bShouldUseSynchronousLoad = _bSynchronous; }

	void InitPrimaryScanClass();
	void LoadResourceTable();
	void ReleaseResourceTable();
	void ScanPathFromResourceRecord_Debug(TArray<CSBaseResourceRecord*> _arrBaseResourceRecords);
	void ScanPathFromResourceRecord(TArray<CSBaseResourceRecord*> _arrBaseResourceRecords);

	/** Parses AssetData to extract the primary type/name from it. This works even if it isn't in the directory */
	virtual FPrimaryAssetId ExtractPrimaryAssetIdFromData(const FAssetData& AssetData, FPrimaryAssetType SuggestedType = NAME_None) const override;
	
private:
	UPROPERTY()
	TMap<FPrimaryAssetType, UClass*> m_PrimaryScanClass;
	UPROPERTY()
	TMap<FName /* Loaded UClass Name */, UClass*> m_LoadedUClass;
};

#define g_AssetMgrValid ( (UCSAssetManager::IsValid()) )
#define g_AssetMgr ( ::Cast<UCSAssetManager>(UCSAssetManager::GetIfValid()) )
