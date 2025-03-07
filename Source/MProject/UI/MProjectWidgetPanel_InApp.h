// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InAppPurchaseCallbackProxy2.h"
#include "InAppPurchaseDataTypes.h"
#include "UILibrary/Widget/CSWidgetPanel.h"
#include "MProjectWidgetPanel_InApp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInAppPurchaseCallbackProxy2_OnSuccess, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>&, Receipts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInAppPurchaseCallbackProxy2_OnFailure, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>&, Receipts);
UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNativePurchaseComplete,int,amount,const FString&,type);
class UCSButton;
class UCSTextBlock;
UCLASS()
class MPROJECT_API UMProjectWidgetPanel_InApp : public UCSWidgetPanel
{
	GENERATED_BODY()
public:

	static FNativePurchaseComplete NativePurchaseComplete;
	
	static FString strType;
	static int Amount;
public:

	virtual void InitData() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	virtual void Show(ESlateVisibility visible = ESlateVisibility::SelfHitTestInvisible, float fDelayTime = 0.f, float fFadeTime = 0.f, float fDisplayTime = 0.f) override;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Buy_500C;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Buy_1000C;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Buy_2000C;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSButton* Button_Back;
	UPROPERTY(meta = (BindWidgetOptional))
	UCSTextBlock* TextBlock_Buy;
private:
	UFUNCTION()
	void OnPurchaseSuccessTo(EInAppPurchaseStatus PurchaseStatus, const FInAppPurchaseReceiptInfo2& InAppPurchaseReceipt);
	UFUNCTION()
	void OnPurchaseFailureTo(EInAppPurchaseStatus PurchaseStatus, const FInAppPurchaseReceiptInfo2& InAppPurchaseReceipt);
	UFUNCTION()
	void OnClick_Buy500C();
	UFUNCTION()
	void OnPurchaseSuccess(EInAppPurchaseStatus PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>& InAppPurchaseReceipts);
	UFUNCTION()
	void OnPurchaseFailure(EInAppPurchaseStatus PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>& InAppPurchaseReceipts);
	UFUNCTION()
	void OnClick_Buy1000C();
	UFUNCTION()
	void OnClick_Buy2000C();
	UFUNCTION()
	void OnClick_Back();
	UFUNCTION()
	void ChangeTestText(const FString& text);

	UFUNCTION()
	void HandlePurchaseResult(int amount, const FString& Type);
	
#if PLATFORM_ANDROID
	static void onNativePurchaseResult(JNIEnv* env, jobject obj, jint amount , jstring type);
#endif
};
