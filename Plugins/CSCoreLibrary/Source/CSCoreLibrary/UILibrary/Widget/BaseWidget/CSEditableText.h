// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableText.h"
#include "TableLibrary/Define/CSCommon_FunctionProperty.h"
#include "CSEditableText.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSEditableText : public UEditableText
{
	GENERATED_BODY()
public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	FText ChangeText(nLocalType::en _elocalType,FText InText);

	void ChangeLocal(nLocalType::en _elocalType);

	FText RefreshTid();
private:
	UPROPERTY(meta = (MultiLine = true))
	FString m_strText = "";
	UPROPERTY(meta = (MultiLine = true))
	FString m_strChangeText = "";

	FName m_strTid = "";
};
