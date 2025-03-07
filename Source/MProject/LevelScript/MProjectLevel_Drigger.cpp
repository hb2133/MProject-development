// MProjectLevel_Drigger.cpp
#include "MProjectLevel_Drigger.h"

#include "CoreLibrary/Manager/CSFileManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MProject/UI/MProjectWidget_Tutorial.h"
#include "Camera/CameraActor.h"

AMProjectLevel_Drigger::AMProjectLevel_Drigger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMProjectLevel_Drigger::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//카메라 블렌드
	if (PlayerController)
	{
		TArray<AActor*> FoundCameras;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

		AActor* StartCamera = nullptr;
		for (AActor* Actor : FoundCameras)
		{
			if (Actor->ActorHasTag("StartCamera"))
			{
				StartCamera = Actor;
				break;
			}
		}
		if (StartCamera)
		{
			PlayerController->SetViewTargetWithBlend(StartCamera, 0.0f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Start_Cam 태그가 지정된 카메라를 찾을 수 없습니다."));
		}

		PlayerController->SetShowMouseCursor(true);
		//임시
		//PlayerController->SetInputMode(FInputModeUIOnly());

		//튜토리얼 위젯
		if (UClass* pTutorialWidgetClass = g_FileMgr->LoadObject<UClass>(nResourceType::UClass, "W_Tutorial_BP"))
		{
			if (UMProjectWidget_Tutorial* pTutorialWidget = CreateWidget<UMProjectWidget_Tutorial>(PlayerController, pTutorialWidgetClass))
			{
				pTutorialWidget->SetVisibility(ESlateVisibility::Visible);
				pTutorialWidget->AddToViewport();
			}
		}
	}
}




void AMProjectLevel_Drigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}
