// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSSingleton.h"
#include "CoreLibrary/Define/CSCommon_File.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"
#include "UObject/ConstructorHelpers.h"

class CSCORELIBRARY_API CSFileManager : public CSSingleton<CSFileManager>
{
public:
	void Release() override;
	void Load() override;

private:
	TMap<FName, FolderPathNodePtr> m_AssetFileMap;
	TMultiMap<FName, FolderPathNodePtr> m_AssetDirMap;

#if WITH_EDITOR && PLATFORM_WINDOWS
	TMap<FName, TArray<FName>> m_ErrorLog;
#endif

	FString m_BaseProjectDir = FString("");
	FString m_BaseContentDir = FString("");

	void LoadAssetPath();
	void ReleaseAssetPath();

	bool GetPathFromPathNode(FolderPathNode* _pNode, FString& OUT _strPath, const bool& _bFullPath);

	void SearchSubDirPath(FString& _Path, FolderPathNode* _Parent, IFileManager& _FileManager, int _nDepth);
	bool CheckOverlapPath(FString& _fileName, FolderPathNode* _CheckNode);

	void AddErrorLog(const FString& _fileName, const FString& _Path);
	void PrintErrorLog();

public:
	bool CheckAssetPath(const FName& _strName);
	bool GetAssetPath(const FName& _strName, FString& OUT _strPath, const bool& _bFullPath = false);
	bool GetAssetPath(const nResourceType::en& _eType, const FName& _strName, FString& OUT _strPath);

	FString ConvertPathByResourceType(const nResourceType::en& _eType, FString _strPath, FName _strFileName);
	UBlueprintGeneratedClass* GetBlueprintGeneratedClass(const FName& _strBPName);

private:
	template<typename T>
	T* ConstructorHelpers(const FString& _strFullPath)
	{
		ConstructorHelpers::FObjectFinder<T> _Data(*_strFullPath);
		return ::Cast<T>(_Data.Object);
	}

	template<typename T>
	T* LoadObject(const FString& _strFullPath)
	{
		//수정했습니다
		FSoftObjectPath _stAssetReference(*_strFullPath);
		UObject* _pObject = _stAssetReference.TryLoad();

		return ::Cast<T>(_pObject);
	}

public:
	template<typename T>
	T* ConstructorHelpers(const nResourceType::en& _eType, const FName& _strFile)
	{
		FString _strPath;
		if (this->GetAssetPath(_eType, _strFile, _strPath))
			return this->ConstructorHelpers<T>(_strPath);
		return nullptr;
	}

	template<typename T>
	T* LoadObject(const nResourceType::en& _eType, const FName& _strFile)
	{
		FString _strPath;
		if (this->GetAssetPath(_eType, _strFile, _strPath))
			return this->LoadObject<T>(_strPath);
		return nullptr;
	}

public: 
};
template class CSSingleton<CSFileManager>;

#define g_FileMgr ( CSFileManager::GetInstance() )
