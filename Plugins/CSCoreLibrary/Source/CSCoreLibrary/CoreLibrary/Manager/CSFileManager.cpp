// Fill out your copyright notice in the Description page of Project Settings.

#include "CSFileManager.h"
#include "Misc/Paths.h"

#if WITH_EDITOR && PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include <consoleapi.h>
#include <io.h>
#include <string>
#include <shellapi.h>
#endif

void CSFileManager::Release()
{	
	this->ReleaseAssetPath();
}

void CSFileManager::Load()
{
	m_BaseProjectDir = FPaths::ProjectDir();
	m_BaseContentDir = FPaths::ProjectContentDir();

	this->LoadAssetPath();
}

void CSFileManager::LoadAssetPath()
{
	IFileManager& FileManager = IFileManager::Get();

	this->ReleaseAssetPath();
	this->SearchSubDirPath(m_BaseContentDir, nullptr, FileManager, 0);

#if WITH_EDITOR && PLATFORM_WINDOWS
	this->PrintErrorLog();
#endif
}

void CSFileManager::ReleaseAssetPath()
{
	m_AssetFileMap.Empty();
	m_AssetDirMap.Empty();

#if WITH_EDITOR && PLATFORM_WINDOWS
	m_ErrorLog.Empty();
#endif
}

bool CSFileManager::GetPathFromPathNode(FolderPathNode* _pNode, FString& OUT _strPath, const bool& _bFullPath)
{
	if (_pNode)
	{
		FolderPathNode* _pFindNode = _pNode;
		if (_pFindNode->_pParent != nullptr)
		{
			if (_bFullPath)
				_strPath = _pFindNode->_CurNodeName.ToString();

			do
			{
				_strPath = (_pFindNode->_pParent->_CurNodeName).ToString() + FString("/") + _strPath;
				_pFindNode = _pFindNode->_pParent;
			} while (_pFindNode->_pParent != nullptr);
		}

		_strPath = FString("/game/") + _strPath;
		return true;
	}
	return false;
}

void CSFileManager::SearchSubDirPath(FString& _Path, FolderPathNode* _Parent, IFileManager& _FileManager, int _nDepth)
{
	FString _strSearchPath = FString::Printf(TEXT("%s*"), *_Path);

	TArray<FString> SearchFile;
	TArray<FString> SearchSubDir;

	_FileManager.FindFiles(SearchFile, *_strSearchPath, true, false);
	_FileManager.FindFiles(SearchSubDir, *_strSearchPath, false, true);

	for (auto iter : SearchSubDir)
	{
		TSharedPtr<FolderPathNode> _Node = MakeShareable(new FolderPathNode);
		_Node.Get()->_pParent = _Parent;
		_Node.Get()->_CurNodeName = *iter;

		m_AssetDirMap.Add(*iter, _Node);

		FString _dirName = iter;
		FString _NextPath = _Path + iter + FString("/");

		//if (_dirName != TEXT("Table")) //:: 탐색목록에서 제외하고싶은 폴더가 있으면 여기에 적는다.
		this->SearchSubDirPath(_NextPath, _Node.Get(), _FileManager, _nDepth + 1);
	}

	for (auto iter : SearchFile)
	{
		TSharedPtr<FolderPathNode> _Node = MakeShareable(new FolderPathNode);
		_Node.Get()->_pParent = _Parent;

		FString _fileName;
		iter.Split(TEXT("."), &_fileName, nullptr);
		_Node.Get()->_CurNodeName = *_fileName;

		if (this->CheckOverlapPath(_fileName, _Node.Get()) == false)
			m_AssetFileMap.Add(*_fileName, _Node);
	}
}

bool CSFileManager::CheckOverlapPath(FString& _fileName, FolderPathNode* _CheckNode)
{
	if (m_AssetFileMap.Contains(*_fileName))
	{
		FString _OriginPath, _OverlapPath;
		this->GetAssetPath(*_fileName, _OriginPath, true);

		//UE_LOG(LogTemp, Log, TEXT("CSFileMgr::CheckOverlapPath - Same Asset Name Exist : %s"), *_OriginPath);

#if WITH_EDITOR && PLATFORM_WINDOWS
		//:: Add Error Log
		this->GetPathFromPathNode(_CheckNode, _OverlapPath, true);
		this->AddErrorLog(_fileName, *_OverlapPath);
#endif
		return true;
	}
	return false;
}

void CSFileManager::AddErrorLog(const FString& _fileName, const FString& _Path)
{
#if WITH_EDITOR && PLATFORM_WINDOWS
	if (m_ErrorLog.Contains(*_fileName))
	{
		auto iter = m_ErrorLog.FindAndRemoveChecked(*_fileName);
		iter.Add(*_Path);
		m_ErrorLog.Add(*_fileName, iter);
	}
	else
	{
		TArray<FName> _CurPath;
		_CurPath.Add(*_Path);
		m_ErrorLog.Add(*_fileName, _CurPath);
	}
#endif
}

void CSFileManager::PrintErrorLog()
{
#if WITH_EDITOR && PLATFORM_WINDOWS
	//::중복 파일 에러 로그 출력
	if (m_ErrorLog.Num())
	{
		TArray<FString> _arrLog;
		_arrLog.Add(FString::Printf(TEXT("Duplicate Asset File!!!!!")));
		_arrLog.Add(FString::Printf(TEXT("Check Please!")));
		_arrLog.Add(FString::Printf(TEXT("")));
		_arrLog.Add(FString::Printf(TEXT(" * Total Count : %d"), m_ErrorLog.Num()));
		_arrLog.Add(FString::Printf(TEXT("")));
		_arrLog.Add(FString::Printf(TEXT("")));
		_arrLog.Add(FString::Printf(TEXT("")));

		for (auto _fileiter : m_ErrorLog)
		{
			//*(_fileiter.Value).ToString();
			_arrLog.Add(FString::Printf(TEXT("-------")));
			_arrLog.Add(FString::Printf(TEXT("")));
			_arrLog.Add(FString::Printf(TEXT("Duplicate File Name : %s"), *_fileiter.Key.ToString()));
			_arrLog.Add(FString::Printf(TEXT("")));
			_arrLog.Add(FString::Printf(TEXT("Original Path : ")));
			_arrLog.Add(FString::Printf(TEXT("")));

			FString _OriginPath;
			this->GetAssetPath(*_fileiter.Key.ToString(), _OriginPath, true);
			_arrLog.Add(FString::Printf(TEXT("%s"), *_OriginPath));

			_arrLog.Add(FString::Printf(TEXT("")));
			_arrLog.Add(FString::Printf(TEXT("Duplicate Path : ")));
			_arrLog.Add(FString::Printf(TEXT("")));
			for (auto& _pathiter : _fileiter.Value)
			{
				_arrLog.Add(FString::Printf(TEXT("%s"), *_pathiter.ToString()));
			}
			_arrLog.Add(FString::Printf(TEXT("")));
		}

		//:: Write File.
		FString FilePath = FPaths::ConvertRelativePathToFull(m_BaseContentDir) + TEXT("/Warnning_Duplicate_File.txt");
		FFileHelper::SaveStringArrayToFile(_arrLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_NoReplaceExisting);

		//:: File Open
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		//ShellExecute(NULL, L"open", L"notepad", *FilePath, NULL, SW_SHOW);
		PRAGMA_ENABLE_DEPRECATION_WARNINGS
	}
#endif

}

bool CSFileManager::CheckAssetPath(const FName& _strName)
{
	return (m_AssetFileMap.Find(_strName) != nullptr) ? true : false;
}

bool CSFileManager::GetAssetPath(const FName& _strName, FString& OUT _strPath, const bool& _bFullPath /*= false*/)
{
	if (_strName.IsNone())
		return false;

	FolderPathNodePtr* _pNode = m_AssetFileMap.Find(_strName);
	if (_pNode == nullptr || (*_pNode).IsValid() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("CDFileMgr::GetAssetPath() - Don't Find Asset : %s"), *_strName.ToString());
		return false;
	}

	return this->GetPathFromPathNode((*_pNode).Get(), _strPath, _bFullPath);
}

bool CSFileManager::GetAssetPath(const nResourceType::en& _eType, const FName& _strName, FString& OUT _strPath)
{
	FString _Path;
	if (this->GetAssetPath(_strName, _Path, false) == false)
		return false;

	_strPath = this->ConvertPathByResourceType(_eType, _Path, _strName);
	return true;
}

FString CSFileManager::ConvertPathByResourceType(const nResourceType::en& _eType, FString _strPath, FName _strFileName)
{
	FString _strResult;
	switch (_eType)
	{
	case nResourceType::General: //:: "Path/FileName.FileName"
		_strResult = _strPath + _strFileName.ToString() + "." + _strFileName.ToString();
		break;
	case nResourceType::Blueprint: 	//:: "BlueprintGeneratedClass'Path/FileName.FileName_C'"
		_strResult = "BlueprintGeneratedClass'" + _strPath + _strFileName.ToString() + "." + _strFileName.ToString() + "_C'";
		break;
	case nResourceType::UClass: //:: "Class'Path/FileName.FileName_C'" "
		_strResult = "Class'" + _strPath + _strFileName.ToString() + "." + _strFileName.ToString() + "_C'";
		break;
	}
	_strResult = _strResult.Replace(TEXT("\\"), TEXT("/"));
	_strResult = _strResult.Replace(TEXT("//"), TEXT("/"));

	return _strResult;
}

UBlueprintGeneratedClass* CSFileManager::GetBlueprintGeneratedClass(const FName& _strBPName)
{
	return this->LoadObject<UBlueprintGeneratedClass>(nResourceType::Blueprint, _strBPName);
}