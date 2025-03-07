// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_Tutorial.generated.h"

class UCSButton;
class UCSCanvasPanel;
class UMProjectWidget_Running;
class UCSImage;
class UMediaPlayer;
UCLASS()
class MPROJECT_API UMProjectWidget_Tutorial : public UCSUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
public:
	UFUNCTION()
	void OnClick_Start();
	void PlaySoundButton();

public:
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_Start;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSCanvasPanel* Canvas_Panel;

	UPROPERTY(meta=(BindWidgetOptional))
	UMProjectWidget_Running* W_Running_BP;

	UPROPERTY(meta=(BindWidgetOptional))
	UMProjectWidget_Running* W_DriggerBP;

public:
	UPROPERTY(BlueprintReadWrite)
	bool m_bVideoReset;
	
};
