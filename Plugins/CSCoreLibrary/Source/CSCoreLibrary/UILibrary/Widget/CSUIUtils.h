// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceLibrary/Define/CSDefine_Resource.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "UILibrary/DataTable/DataRecord/CSUIDataRecord.h"

class UWorld;
class UCSImage;
class UTexture2D;
class UPaperSprite;
class CSViewImageRecord;

class CSCORELIBRARY_API CSUIUtils
{
private:
	static UCSUserWidgetBase* CreateWidgetBase(const FName& _strBPName, UWorld* _pWorld = nullptr);

public:
	static FString ConvertPath(const nResourceType::en& _eType, const FName& _strFolderPath, const FName& _strFileName);

	template <typename T = UCSUserWidgetBase>
	static T* LoadWidget(CSUIDataRecord* _pRecord, UWorld* pWorld = nullptr)
	{
		T* _pWidget = nullptr;
		if (_pRecord)
		{
			if (UCSUserWidgetBase* _pWidgetBase = CreateWidgetBase(_pRecord->_strUIBPName, pWorld))
			{
				_pWidget = ::Cast<T>(_pWidgetBase);
				if (_pWidget != nullptr)
					_pWidget->SetParentWidgetForWidgetTree();
				else
					_pWidgetBase->ConditionalBeginDestroy();
			}
		}
		return _pWidget;
	}

	template <typename T = UCSUserWidgetBase>
	static T* LoadWidget(const FName& _strBPName, UWorld* pWorld = nullptr)
	{
		T* _pWidget = nullptr;
		if (UCSUserWidgetBase* _pWidgetBase = CreateWidgetBase(_strBPName, pWorld))
		{
			_pWidget = ::Cast<T>(_pWidgetBase);
			if(_pWidget == nullptr)
				_pWidgetBase->ConditionalBeginDestroy();
		}
		return _pWidget;
	}

	static bool DestroyWidget(UCSUserWidgetBase* pBase);

	//:: Texture
	static UTexture2D* LoadTexture(const FString& strTextureName);
	static UPaperSprite* LoadSprite(const FString& strSpriteName);

	static void ToggleWidget(UCSUserWidgetBase* pWidget, bool bSelfHitTestInvisible = true);
	static void ToggleWidget(UWidget* pWidget, bool bSelfHitTestInvisible = true);
};
