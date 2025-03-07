// Fill out your copyright notice in the Description page of Project Settings.


#include "MPAdMobMgr.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <jni.h>
#endif

FNativeRewardComplete UMPAdMobMgr::NativeRewardComplete;
int UMPAdMobMgr::Amount;
FString UMPAdMobMgr::strType;

void UMPAdMobMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMPAdMobMgr::Deinitialize()
{
	UMPAdMobMgr::NativeRewardComplete.Unbind();
	
	Super::Deinitialize();
}

void UMPAdMobMgr::Load()
{
	Super::Load();

	LoadRewardAd("ca-app-pub-3940256099942544/5224354917");
}

void UMPAdMobMgr::Release()
{
	Super::Release();
}

void UMPAdMobMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UMPAdMobMgr::ShowBanner(const FString& _BannerShow)
{
	UE_LOG(LogTemp,Warning,TEXT("Click"))
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		auto BannerId = FJavaHelper::ToJavaString(Env,_BannerShow);

		static jmethodID ShowBanner = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CreateBanner", "(Ljava/lang/String;)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ShowBanner, *BannerId);
	}
#endif
}

void UMPAdMobMgr::LoadInterstitialAd(const FString& _LoadInterstitialId)
{
	UE_LOG(LogTemp,Warning,TEXT("InterstitialAd Load"))
	
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		auto InterstitialId = FJavaHelper::ToJavaString(Env,_LoadInterstitialId);

		static jmethodID LoadInterstitial = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LoadInterstitialAd", "(Ljava/lang/String;)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadInterstitial, *InterstitialId);
	}
#endif
}

void UMPAdMobMgr::ShowInterstitialAd()
{
	UE_LOG(LogTemp,Warning,TEXT("InterstitialAd Show"))
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID ShowInterstitial = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShowInterstitialAd", "()V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ShowInterstitial);
	}
#endif
}

void UMPAdMobMgr::LoadRewardAd(const FString& _LoadRewardId)
{
	UE_LOG(LogTemp,Warning,TEXT("RewardAd Load"))
	FNativeRewardComplete Rewared;
	Rewared.BindDynamic(this,&UMPAdMobMgr::HandleRewardResult);
	
	UMPAdMobMgr::NativeRewardComplete.operator=(Rewared);
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		auto RewardId = FJavaHelper::ToJavaString(Env,_LoadRewardId);

		static jmethodID LoadReward = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LoadRewardAd", "(Ljava/lang/String;)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadReward, *RewardId);
	}
#endif
}

void UMPAdMobMgr::ShowRewardAd()
{
#if WITH_EDITOR
	if(UMPAdMobMgr::NativeRewardComplete.IsBound())
	{
		UE_LOG(LogTemp,Warning,TEXT("ComeDown"))
		UMPAdMobMgr::NativeRewardComplete.Execute(3,"Test");
	}
#endif
	
	UE_LOG(LogTemp,Warning,TEXT("RewardAd Show"))
	
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID ShowReward = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShowRewardAd", "()V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ShowReward);
		//UMPAdMobMgr::NativeRewardComplete.Execute(3,"Test");
	}
#endif
}

void UMPAdMobMgr::Blueprint_CallBackRewardResult(const FNativeRewardComplete& OnReward)
{
	UMPAdMobMgr::NativeRewardComplete.operator=(OnReward);
}

void UMPAdMobMgr::Test(int32 amout, FString type)
{
	//	AsyncTask(ENamedThreads::GameThread,[&]
	//	{

	
	//	});
}

void UMPAdMobMgr::HandleRewardResult(int32 amout, const FString& type)
{
	AsyncTask(ENamedThreads::GameThread,[]
	{
		UGameplayStatics::OpenLevel(g_GameGlobal->GetCurWorld(),"Level_MProject");
	});
	LoadRewardAd("ca-app-pub-3940256099942544/5224354917");
}

#if PLATFORM_ANDROID
extern "C" JNIEXPORT void JNICALL
Java_com_epicgames_unreal_GameActivity_onNativeRewardResult(JNIEnv* env, jobject obj, jint amount , jstring type)
{

	const char* nativeString = env->GetStringUTFChars(type, 0);

	UMPAdMobMgr::Amount = amount;

	
	// 콜백 처리
	UMPAdMobMgr::strType = UTF8_TO_TCHAR(nativeString);
	UE_LOG(LogTemp, Log, TEXT("Received result: %s"), *UMPAdMobMgr::strType);
	AsyncTask(ENamedThreads::GameThread,[&]
	{
		if(UMPAdMobMgr::NativeRewardComplete.IsBound())
		{
			UE_LOG(LogTemp,Warning,TEXT("ComeDown"))
			UMPAdMobMgr::NativeRewardComplete.Execute(UMPAdMobMgr::Amount,UMPAdMobMgr::strType);
		}
	});

	// JNI 메모리 해제
	env->ReleaseStringUTFChars(type, nativeString);
}
#endif