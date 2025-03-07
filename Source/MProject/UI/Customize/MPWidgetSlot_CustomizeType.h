// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSWidgetSlot.h"
#include "MPWidgetSlot_CustomizeType.generated.h"

UCLASS()
class MPROJECT_API UMPWidgetSlot_CustomizeType : public UCSWidgetSlot
{
	GENERATED_BODY()

public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

	void SetCustomizeType(const FString& customizeType);
	FString GetCustomizeType() const { return m_strCustomizeType; }

private:
	FString m_strCustomizeType;
};
