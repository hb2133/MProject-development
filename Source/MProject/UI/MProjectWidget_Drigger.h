// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "MProjectWidget_Drigger.generated.h"

class UCSButton;
class UCSTextBlock;
class UCSCanvasPanel;
class UCSImage;
class ACSActor;
class UMProjectWidget_Ending;
UCLASS()
class MPROJECT_API UMProjectWidget_Drigger : public UCSUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

public:
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_R;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_G;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_B;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_EXIT;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSButton* Button_GameClear;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Timer;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSTextBlock* TextBlock_Score;
	
	UPROPERTY(meta=(BindWidgetOptional))
	UCSCanvasPanel* Canvas_GameClear;
	
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Warning;

	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Health1;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Health2;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_Health3;
	UPROPERTY(meta=(BindWidgetOptional))
	UCSImage* Image_GameClear;

	UPROPERTY(meta=(BindWidgetOptional))
	UMProjectWidget_Ending* W_Ending_BP;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	UWidgetAnimation* Warning_Animation;
	FWidgetAnimationDynamicEvent Warning_EndDelegate;
	UPROPERTY(BlueprintReadOnly, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	UWidgetAnimation* TouchText_Animation;
	
private:
	UFUNCTION()
	void OnClick_R();
	UFUNCTION()
	void OnClick_G();
	UFUNCTION()
	void OnClick_B();
	UFUNCTION()
	void OnClick_EXIT();
	UFUNCTION()
	void OnClick_GameClear();
	
	UFUNCTION()
	void Warning_AnimationPlay();
	UFUNCTION()
	void Warning_AnimationFinished();
	UFUNCTION()
	void TouchText_AnimationPlay();
	UFUNCTION()
	void UpdateDiggerHPLog(int32 NewHP);
	UFUNCTION()
	void UpdateDiggerScoreLog(int32 NewScore);

	UFUNCTION()
	void OnTimerFinished();
	UFUNCTION()
	void OnDelayedAnimationPlay();

	int32 Seconds;
	int32 Milliseconds;
	float AccumulatedTime; // 누적 시간 관리 변수
	bool bIsTimerActive;

	FTimerHandle SoundTimerHandle;
	void OnClickBackLevel();
	UPROPERTY()
	AActor* FoundActor;
};
