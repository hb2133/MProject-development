// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_Running.generated.h"

class UCSButton;
class UCSTextBlock;
class UCSCanvasPanel;
class UCSImage;
class UMProjectWidget_Ending;
UCLASS()
class MPROJECT_API UMProjectWidget_Running : public UCSUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

public:
	UFUNCTION()
	void OnClick_GameClear();
	UFUNCTION()
	void OnClick_EXIT();
	UFUNCTION()
	void OnClick_R();
	UFUNCTION()
	void OnPressed_R();
	UFUNCTION()
	void OnPressed_G();
	UFUNCTION()
	void OnPressed_B();
	UFUNCTION()
	void OnClick_G();
	UFUNCTION()
	void OnClick_B();
	UFUNCTION()
	void UpdateButtonState(UCSTextBlock* testnum, int32 clicknum);

public:
	UPROPERTY(meta=(BindWidgetOptional))
	UCSCanvasPanel* Canvas_GameClear;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_GameClear;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_EXIT;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Health1;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Health2;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Health3;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_GameClear;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Warning;
	
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_R;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_G;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_B;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Timer;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Score;

	UPROPERTY(meta=(BindWidgetOptional))
	UMProjectWidget_Ending* W_Ending_BP;

	//==테스트==
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBock_TestNum1;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBock_TestNum2;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBock_TestNum3;

public:
	UFUNCTION()
	void UpdateHPLog(int32 NewHP);
	UFUNCTION()
	void UpdateScoreLog(int32 NewScore);
	UFUNCTION()
	void Warning_AnimationPlay();
	UFUNCTION()
	void Warning_AnimationFinished();
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBock_CheckState;
	UPROPERTY(BlueprintReadOnly, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	UWidgetAnimation* Warning_Animation;
	FWidgetAnimationDynamicEvent Warning_EndDelegate;
	UPROPERTY(BlueprintReadOnly, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	UWidgetAnimation* TouchText_Animation;
	
private:
	bool m_bCheatMode = false;
	int32 TestClickNum1;
	int32 TestClickNum2;
	int32 TestClickNum3;
	
	bool bIsGreenPressed;
	bool bIsRedPressed;
	bool bIsBluePressed;

	bool bIsClear;

	void OnTimerFinished();
	void OnDelayedAnimationPlay();
	void TouchText_AnimationPlay();
	UFUNCTION()
	void ClearLog();

	int32 m_iSeconds;
	int32 Milliseconds;
	float AccumulatedTime;
	bool bIsTimerActive;

	FTimerHandle SoundTimerHandle;
	void OnClickBackLevel();
};
