// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "UILibrary/Widget/BaseWidget/CSSlider.h"
#include "MProjectWidget_Settings.generated.h"

class UCSButton;
class UCSCanvasPanel;
class UCSSlider;
class UCSImage;
UCLASS()
class MPROJECT_API UMProjectWidget_Settings : public UCSUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* ButtonStart;
	
	UPROPERTY(meta=(BindWidgetOptional))
	UCSCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSSlider* SliderBGM;

	UPROPERTY(meta = (BindWidgetOptional))
	UCSSlider* SliderBtn;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* ButtonMuteBGM;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* ButtonMuteBtn;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* ImgMuteBGM;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* ImgMuteBtn;

public:
	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnBGMVolumeChanged(float BGMVolume);
	UFUNCTION()
	void OnBtnVolumeChanged(float BtnVolume);

	UFUNCTION()
	void OnMuteBGMButtonClicked();
	UFUNCTION()
	void OnMuteBtnButtonClicked();
	
protected:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;


private:
	float m_BGMVolume = 2.0f;
	float m_BtnVolume = 2.0f;

	FString m_strMuteImgName;
	FString m_strUnmuteImgName;
};