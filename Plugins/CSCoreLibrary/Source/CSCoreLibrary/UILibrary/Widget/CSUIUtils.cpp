// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUIUtils.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "UILibrary/Widget/BaseWidget/CSImage.h"
#include "UObject/SoftObjectPath.h"

#include "UILibrary/DataTable/DataRecord/CSViewImageRecord.h"
#include "CoreLibrary/Manager/CSFileManager.h"


UCSUserWidgetBase* CSUIUtils::CreateWidgetBase(const FName& _strBPName, UWorld* _pWorld /*= nullptr*/)
{
	UCSUserWidgetBase* _pWidget = nullptr;

	if (_pWorld)
	{
		FString _strFilePath = FString("");
		g_FileMgr->GetAssetPath(nResourceType::Blueprint, _strBPName, _strFilePath);

		if (_strFilePath.IsEmpty() == false)
		{
			//수정했습니다.
			FSoftClassPath _refClass(_strFilePath);
			UClass* _pWidgetClass = _refClass.ResolveClass();

			if (_pWidgetClass == nullptr)
				_pWidgetClass = _refClass.TryLoadClass<UCSUserWidgetBase>();

			if (_pWidgetClass)
			{
				_pWidget = CreateWidget<UCSUserWidgetBase>(_pWorld, _pWidgetClass);
				if (_pWidget == nullptr)
					UE_LOG(LogTemp, Warning, TEXT("CSUIUtils :: CreateWidgetFail"));
			}
		}
	}
	return _pWidget;
}

FString CSUIUtils::ConvertPath(const nResourceType::en& _eType, const FName& _strFolderPath, const FName& _strFileName)
{
	FString strResult;
	switch (_eType)
	{
	case nResourceType::Blueprint:
		strResult = FString::Printf(TEXT("BlueprintGeneratedClass'%s%s.%s_c'"), *_strFolderPath.ToString(), *_strFileName.ToString(), *_strFileName.ToString());
		break;

	default:
		strResult = FString::Printf(TEXT("%s%s.%s"), *_strFolderPath.ToString(), *_strFileName.ToString(), *_strFileName.ToString());
		break;
	}

	strResult = strResult.Replace(TEXT("\\"), TEXT("/"));
	strResult = strResult.Replace(TEXT("//"), TEXT("/"));
	
	return strResult;
}

bool CSUIUtils::DestroyWidget(UCSUserWidgetBase* pBase)
{
	if (pBase == nullptr)
		return false;

	pBase->RemoveFromParent();

	return pBase->ConditionalBeginDestroy();
}

UTexture2D* CSUIUtils::LoadTexture(const FString& strTextureName)
{
	if (strTextureName.IsEmpty())
		return nullptr;

	return g_FileMgr->LoadObject<UTexture2D>(nResourceType::General, *strTextureName);	
}

UPaperSprite* CSUIUtils::LoadSprite(const FString& strSpriteName)
{
	if(strSpriteName.IsEmpty())
		return nullptr;

	return g_FileMgr->LoadObject<UPaperSprite>(nResourceType::General, *strSpriteName);
}

void CSUIUtils::ToggleWidget(UCSUserWidgetBase* pWidget, bool bSelfHitTestInvisible)
{
	ESlateVisibility eVisibility = bSelfHitTestInvisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Visible; 
	if(pWidget)
	{
		if(pWidget->IsActive())
		{
			pWidget->Hide();
		}
		else
		{
			pWidget->Show(eVisibility);
		}						
	}
}

void CSUIUtils::ToggleWidget(UWidget* pWidget , bool bSelfHitTestInvisible)
{
	ESlateVisibility eVisibility = bSelfHitTestInvisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Visible;
	if(pWidget)
	{
		pWidget->SetVisibility(pWidget->GetVisibility() == ESlateVisibility::Collapsed ? eVisibility : ESlateVisibility::Collapsed);
	}
}

