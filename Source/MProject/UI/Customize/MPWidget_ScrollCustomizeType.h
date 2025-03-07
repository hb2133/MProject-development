// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/WidgetInterface/CSWidgetScrollBox.h"
#include "MPWidget_ScrollCustomizeType.generated.h"

UCLASS()
class MPROJECT_API UMPWidget_ScrollCustomizeType : public UCSWidgetScrollBox
{
	GENERATED_BODY()

public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	virtual void SynchronizeProperties() override;
};
