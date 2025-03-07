// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectWidgetPanel_InApp.h"


#include "InAppPurchaseDataTypes.h"
#include "Kismet/GameplayStatics.h"
#include "UILibrary/Manager/CSUIMgr.h"
#include "UILibrary/Widget/BaseWidget/CSButton.h"
#include "UILibrary/Widget/BaseWidget/CSTextBlock.h"
FNativePurchaseComplete UMProjectWidgetPanel_InApp::NativePurchaseComplete;
int UMProjectWidgetPanel_InApp::Amount;
FString UMProjectWidgetPanel_InApp::strType;
void UMProjectWidgetPanel_InApp::InitData()
{
    UCSWidgetPanel::InitData();

    FNativePurchaseComplete Purchase;
    Purchase.BindDynamic(this,&UMProjectWidgetPanel_InApp::HandlePurchaseResult);
	
    UMProjectWidgetPanel_InApp::NativePurchaseComplete.operator=(Purchase);
}

void UMProjectWidgetPanel_InApp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    UCSWidgetPanel::NativeTick(MyGeometry, InDeltaTime);
}

void UMProjectWidgetPanel_InApp::LinkEvent()
{
    UCSWidgetPanel::LinkEvent();

    BIND_BUTTON_EVENT(Button_Buy_500C, &UMProjectWidgetPanel_InApp::OnClick_Buy500C);
    BIND_BUTTON_EVENT(Button_Buy_1000C, &UMProjectWidgetPanel_InApp::OnClick_Buy1000C);
    BIND_BUTTON_EVENT(Button_Buy_2000C, &UMProjectWidgetPanel_InApp::OnClick_Buy2000C);
    BIND_BUTTON_EVENT(Button_Back, &UMProjectWidgetPanel_InApp::OnClick_Back);
}

void UMProjectWidgetPanel_InApp::UnLinkEvent()
{
    UNBIND_BUTTON_EVENT_ALL(Button_Buy_500C);
    UNBIND_BUTTON_EVENT_ALL(Button_Buy_1000C);
    UNBIND_BUTTON_EVENT_ALL(Button_Buy_2000C);
    
    UCSWidgetPanel::UnLinkEvent();
}

void UMProjectWidgetPanel_InApp::Show(ESlateVisibility visible, float fDelayTime, float fFadeTime, float fDisplayTime)
{
    UCSWidgetPanel::Show(visible, fDelayTime, fFadeTime, fDisplayTime);
}

void UMProjectWidgetPanel_InApp::OnClick_Buy500C()
{
    TArray<FString> arrProductId ;
    arrProductId.Emplace("test_add_1000c");
    arrProductId.Emplace("test_add_500c");
    arrProductId.Emplace("test_add_2000c");


    FString ProductTo = TEXT("test_add_500c");
#if PLATFORM_ANDROID

    //array 구매 정보 버전
    // if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    // {
    //     jclass clsArrayList = Env->FindClass("java/util/ArrayList");
    //     jmethodID mCtor = Env->GetMethodID(clsArrayList,"<init>","()V");
    //     jmethodID mAdd = Env->GetMethodID(clsArrayList,"add","(Ljava/lang/Object;)Z");
    //     jobject resultArray = Env->NewObject(clsArrayList,mCtor);
    //
    //     for(FString ProductId : arrProductId)
    //     {
    //         auto Productid = FJavaHelper::ToJavaString(Env,ProductId);
    //         Env->CallBooleanMethod(resultArray,mAdd,Env->NewStringUTF(TCHAR_TO_UTF8(*ProductId)));
    //     }
		  //
    //
    //     static jmethodID QueryProducts = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_QueryProducts", "(Ljava/util/ArrayList;)V", false);
    //
    //     FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, QueryProducts, resultArray);
    // }

    //단일 구매 정보 버전
    
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        auto Productid = FJavaHelper::ToJavaString(Env,ProductTo);
        static jmethodID QueryProducts = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LaunchPurchaseFlow", "(Ljava/lang/String;)V", false);
    
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, QueryProducts, *Productid);
    }
#endif
// //#if PLATFORM_ANDROID
//     // 구매 요청 생성
//     FInAppPurchaseProductRequest2 Request;
//     Request.ProductIdentifier = TEXT("test_add_500c");
//
//     // 인앱 결제 시작
//     auto PurchaseCallbackProxy = UInAppPurchaseCheckoutCallbackProxy::CreateProxyObjectForInAppPurchaseCheckout(GetWorld()->GetFirstPlayerController(), Request);
//
//     // 성공 콜백 연결
//     PurchaseCallbackProxy->OnSuccess.AddDynamic(this, &UMProjectWidgetPanel_InApp::OnPurchaseSuccessTo);
//
//     // 실패 콜백 연결
//     PurchaseCallbackProxy->OnFailure.AddDynamic(this, &UMProjectWidgetPanel_InApp::OnPurchaseFailureTo);
// //#endif
}
#if PLATFORM_ANDROID
extern "C" JNIEXPORT void JNICALL
Java_com_epicgames_unreal_GameActivity_onNativePruchaseResult(JNIEnv* env, jobject obj, jint amount , jstring type)
{

    const char* nativeString = env->GetStringUTFChars(type, 0);

    UMProjectWidgetPanel_InApp::Amount = amount;

	
    // 콜백 처리
    UMProjectWidgetPanel_InApp::strType = UTF8_TO_TCHAR(nativeString);
    UE_LOG(LogTemp, Log, TEXT("Received result: %s"), *UMProjectWidgetPanel_InApp::strType);
    AsyncTask(ENamedThreads::GameThread,[&]
    {
        if(UMProjectWidgetPanel_InApp::NativePurchaseComplete.IsBound())
        {
            UE_LOG(LogTemp,Warning,TEXT("ComeDown"))
            UMProjectWidgetPanel_InApp::NativePurchaseComplete.Execute(UMProjectWidgetPanel_InApp::Amount,UMProjectWidgetPanel_InApp::strType);
        }
    });

    // JNI 메모리 해제
    env->ReleaseStringUTFChars(type, nativeString);
}
#endif
void UMProjectWidgetPanel_InApp::OnPurchaseSuccess(EInAppPurchaseStatus PurchaseStatus,
    const TArray<FInAppPurchaseReceiptInfo2>& InAppPurchaseReceipts)
{
    TextBlock_Buy->SetText(FText::FromString("Buy"));
}

void UMProjectWidgetPanel_InApp::OnPurchaseFailure(EInAppPurchaseStatus PurchaseStatus,
    const TArray<FInAppPurchaseReceiptInfo2>& InAppPurchaseReceipts)
{
    TextBlock_Buy->SetText(FText::FromString("error"));
}

void UMProjectWidgetPanel_InApp::OnPurchaseSuccessTo(EInAppPurchaseStatus PurchaseStatus,
                                                     const FInAppPurchaseReceiptInfo2& InAppPurchaseReceipt)
{
    // UInAppPurchaseFinalizeProxy::CreateProxyObjectForInAppPurchaseFinalize(InAppPurchaseReceipt,GetWorld()->GetFirstPlayerController());
    // TextBlock_Buy->SetText(FText::FromString("Buy"));
}

void UMProjectWidgetPanel_InApp::OnPurchaseFailureTo(EInAppPurchaseStatus PurchaseStatus,
    const FInAppPurchaseReceiptInfo2& InAppPurchaseReceipt)
{
    TextBlock_Buy->SetText(FText::FromString("error"));
}

void UMProjectWidgetPanel_InApp::OnClick_Buy1000C()
{
#if PLATFORM_ANDROID
    FInAppPurchaseProductRequest2 Request;
    Request.ProductIdentifier = TEXT("test_add_1000c");
    auto PurchaseCallBackProxy = UInAppPurchaseCallbackProxy2::CreateProxyObjectForInAppPurchase(GetWorld()->GetFirstPlayerController(),Request);
    PurchaseCallBackProxy->OnSuccess.AddDynamic(this,&UMProjectWidgetPanel_InApp::OnPurchaseSuccess);
    PurchaseCallBackProxy->OnFailure.AddDynamic(this,&UMProjectWidgetPanel_InApp::OnPurchaseFailure);
#endif
}

void UMProjectWidgetPanel_InApp::OnClick_Buy2000C()
{
    // if(UKismetSystemLibrary::IsLoggedIn(UGameplayStatics::GetPlayerController(GetWorld(),0)))
    // {
    //     UShowLoginUICallbackProxy::ShowExternalLoginUI(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0));
    // }
    // //#if PLATFORM_ANDROID
    //     // 구매 요청 생성
    //     FInAppPurchaseProductRequest2 Request;
    //     Request.ProductIdentifier = TEXT("test_add_500c");
    //
    //     // 인앱 결제 시작
    //     auto PurchaseCallbackProxy = UInAppPurchaseCheckoutCallbackProxy::CreateProxyObjectForInAppPurchaseCheckout(GetWorld()->GetFirstPlayerController(), Request);
    //
    //     // 성공 콜백 연결
    //     PurchaseCallbackProxy->OnSuccess.AddDynamic(this, &UMProjectWidgetPanel_InApp::OnPurchaseSuccessTo);
    //
    //     // 실패 콜백 연결
    //     PurchaseCallbackProxy->OnFailure.AddDynamic(this, &UMProjectWidgetPanel_InApp::OnPurchaseFailureTo);
    // //#endif
}

void UMProjectWidgetPanel_InApp::ChangeTestText(const FString& text)
{
    TextBlock_Buy->SetText(FText::FromString(text));
}

void UMProjectWidgetPanel_InApp::HandlePurchaseResult(int amount, const FString& Type)
{
    FString text = FString::FromInt(amount) + Type;
    TextBlock_Buy->SetText(FText::FromString(text));
}


void UMProjectWidgetPanel_InApp::OnClick_Back()
{
    if(g_UIMgrValid)
    {
        g_UIMgr->HideUIPanel(nUIPanelType::InApp);
        g_UIMgr->ShowUIPanel(nUIPanelType::Lobby);
    }
}

