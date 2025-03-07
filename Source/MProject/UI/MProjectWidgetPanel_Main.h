// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSWidgetPanel.h"
#include "MProjectWidgetPanel_Main.generated.h"

class UCSCanvasPanel;
class UCSButton;
class UMProjectWidget_Tutorial;
class UCSVerticalBox;
UCLASS()
class MPROJECT_API UMProjectWidgetPanel_Main : public UCSWidgetPanel
{
	GENERATED_BODY()
public:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

public:	
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Start;
	
public:
	UFUNCTION()
	void OnClick_Start();

};
