#include "MProjectActor_CameraTrigger.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "MProjectActor_Camera.h"

AMProjectActor_CameraTrigger::AMProjectActor_CameraTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	// 프로파일 지정
	TriggerBox->SetCollisionProfileName(TEXT("TriggerMoisture"));
	TriggerBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// 오버랩 이벤트 바인딩
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMProjectActor_CameraTrigger::TriggerMoistureBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AMProjectActor_CameraTrigger::TriggerMoistureEndOverlap);

	// 초기 카메라 인덱스
	Number = 0;
}

void AMProjectActor_CameraTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AMProjectActor_CameraTrigger::Tick(float _dt)
{
	Super::Tick(_dt);
}

void AMProjectActor_CameraTrigger::TriggerMoistureBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("Actor %s entered the trigger."), *OtherActor->GetName());
		
		if (Number >= 0 && Number < CameraArray.Num() && CameraArray[Number])
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(CameraArray[Number]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid camera number or camera not assigned!"));
		}
	}
}

void AMProjectActor_CameraTrigger::TriggerMoistureEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("Actor %s exited the trigger."), *OtherActor->GetName());

		// 다음 카메라로 인덱스 증가
		Number = (Number + 1) % CameraArray.Num();

		// 다음 카메라가 존재하면 카메라 전환
		if (CameraArray.IsValidIndex(Number) && CameraArray[Number])
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(CameraArray[Number]);
		}
		else
		{
			// 유효한 카메라가 없으면 기본 Pawn의 카메라로 돌아감
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				AActor* DefaultPawn = UGameplayStatics::GetActorOfClass(GetWorld(), APawn::StaticClass());
				if (DefaultPawn)
				{
					PlayerController->SetViewTargetWithBlend(DefaultPawn);
					UE_LOG(LogTemp, Warning, TEXT("Returning to DefaultPawn camera!"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("DefaultPawn not found!"));
				}
			}
		}
	}
}
