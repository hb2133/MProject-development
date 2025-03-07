// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "MPAdMobMgr.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FRewardComplete,int,amount,FString,type);
UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNativeRewardComplete,int,amount,const FString&,type);

UCLASS()
class MPROJECT_API UMPAdMobMgr : public UCSBaseManager
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FRewardComplete RewardComplete;

	static FNativeRewardComplete NativeRewardComplete;

	static FString strType;
	static int Amount;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Load() override;
	virtual void Release() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ShowBanner(const FString& _BannerShow);

	UFUNCTION(BlueprintCallable)
	void LoadInterstitialAd(const FString& _LoadInterstitialId);

	UFUNCTION(BlueprintCallable)
	void ShowInterstitialAd();

	UFUNCTION(BlueprintCallable)
	void LoadRewardAd(const FString& _LoadRewardId);

	UFUNCTION(BlueprintCallable)
	void ShowRewardAd();

	UFUNCTION(BlueprintCallable, Category = "Firebase|AdMob|Rewarded Video", meta = (DisplayName = "Events - Rewarded Video", AutoCreateRefTerm="OnReward"))
	static void Blueprint_CallBackRewardResult(const FNativeRewardComplete& OnReward);
	
	static void Test(int32 amout , FString type);
	UFUNCTION()
	void HandleRewardResult(int32 amout,const FString& type);

	FORCEINLINE static FNativeRewardComplete& OnRewarded()
	{
		return NativeRewardComplete;
	}
	
#if PLATFORM_ANDROID
	static void onNativeRewardResult(JNIEnv* env, jobject obj, jint amount , jstring type);
#endif
};

#define g_MPAdMobMgrValid ( g_GameGlobal->IsValidManager<UMPAdMobMgr>() )
#define g_MPAdMobMgr ( g_GameGlobal->GetManager<UMPAdMobMgr>() )        