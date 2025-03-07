#include "MProject_Character.h"
#include "Components/SplineComponent.h"
#include "MProject/Actor/MProjectActor_Spline.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MProject/Manager/MProjectMgr.h"

AMProject_Character::AMProject_Character()
{
    PrimaryActorTick.bCanEverTick = true;
    SplineDistance = 0.0f;
    CurrentSpeed = 0.0f;
    ClickDistance = 10.0f;

    MaxSpeed = 400.0f;
    SpeedDecay = 300.0f;

    bRedButtonPressed = false;
    bGreenButtonPressed = false;
    bBlueButtonPressed = false;

    LapCount = 0; // 현재 바퀴 수 초기화
    TotalLaps = 3; // 바퀴 수
    SpeedMultiplier = 1.0f; // 이동속도 기본 배율

    LastButtonPressed = EButtonType::None; // 버튼 초기화

    m_bGameClear = false;
    m_iPlayerHP = 3;
}

void AMProject_Character::BeginPlay()
{
    Super::BeginPlay();

    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    
    if (CurrentLevelName == "Level_MProject")
    {
        FollowCamera->SetRelativeLocation(FVector(0.0f, 300.0f, 30.0f));
    	FollowCamera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    // Spline Actor 설정
    if (TargetSplineActor == nullptr)
    {
        TArray<AActor*> SplineActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMProjectActor_Spline::StaticClass(), SplineActors);

        if (SplineActors.Num() > 0)
        {
            TargetSplineActor = Cast<AMProjectActor_Spline>(SplineActors[0]);
        }

        if (TargetSplineActor == nullptr || TargetSplineActor->SplineComponent == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("TargetSplineActor 또는 SplineComponent가 설정되지 않았습니다."));
        }
        else
        {
            float SplineLength = TargetSplineActor->SplineComponent->GetSplineLength();
            ClickDistance = SplineLength / 180.0f;
        }
    }
}

void AMProject_Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (m_bGameClear)
    {
        return;
    }

    if (TargetSplineActor && TargetSplineActor->SplineComponent)
    {
        CurrentSpeed = FMath::Clamp(CurrentSpeed - SpeedDecay * DeltaTime, 0.0f, MaxSpeed * SpeedMultiplier);
        SplineDistance += CurrentSpeed * DeltaTime;

        float SplineLength = TargetSplineActor->SplineComponent->GetSplineLength();

        // 바퀴 완료 체크
        if (SplineDistance >= SplineLength)
        {
            SplineDistance -= SplineLength;
            LapCount++;
        	OnPlayerScoreChanged.Broadcast(LapCount);
            if (LapCount >= TotalLaps)
            {
                OnLapComplete(); // 3바퀴 완료 시 함수 호출
                return; // 더 이상 이동하지 않음
            }
        }

        SplineDistance = FMath::Clamp(SplineDistance, 0.0f, SplineLength);
        FVector NewLocation = TargetSplineActor->SplineComponent->GetLocationAtDistanceAlongSpline(SplineDistance, ESplineCoordinateSpace::World);
        FRotator NewRotation = TargetSplineActor->SplineComponent->GetRotationAtDistanceAlongSpline(SplineDistance, ESplineCoordinateSpace::World);

        SetActorLocation(NewLocation);
        SetActorRotation(NewRotation);
    }
}

void AMProject_Character::TESTIncreaseSpeed()
{
	// CheatMode 여부에 따라 속도 배율 적용
	SpeedMultiplier = m_bCHEATMODE ? 2.0f : 1.0f;
	CurrentSpeed = FMath::Clamp(CurrentSpeed + (ClickDistance * 10 * SpeedMultiplier), 0.0f, MaxSpeed * 4.0f * SpeedMultiplier);
}

void AMProject_Character::SetButtonPressed(bool bIsRedButtonPressed, bool bIsGreenButtonPressed, bool bIsBlueButtonPressed)
{
	// CheatMode가 아닐 때만 적용
	if (!m_bCHEATMODE)
	{
		// 마지막으로 눌린 버튼을 추적
		EButtonType CurrentButton = EButtonType::None;
		if (bIsRedButtonPressed && !bGreenButtonPressed && !bBlueButtonPressed)
		{
			CurrentButton = EButtonType::Red;
		}
		else if (!bRedButtonPressed && bIsGreenButtonPressed && !bBlueButtonPressed)
		{
			CurrentButton = EButtonType::Green;
		}
		else if (!bRedButtonPressed && !bGreenButtonPressed && bIsBlueButtonPressed)
		{
			CurrentButton = EButtonType::Blue;
		}

		// 세 버튼이 모두 눌렸을 때 속도 0
		if (bIsRedButtonPressed && bIsGreenButtonPressed && bIsBlueButtonPressed)
		{
			CurrentSpeed = 0.0f;
			UE_LOG(LogTemp, Warning, TEXT("경고!"));
			m_iWarningCount++;
			m_iPlayerHP -= 1;
			OnPlayerHPChanged.Broadcast(m_iPlayerHP);
			GetWorld()->GetTimerManager().SetTimer(ButtonCooldownTimerHandle, this, &AMProject_Character::ResetButtonState, 0.1f, false);
		}
		// 버튼이 번갈아 눌렸을 때 속도 2배 적용
		else if (CurrentButton != LastButtonPressed && (bIsRedButtonPressed || bIsGreenButtonPressed || bIsBlueButtonPressed))
		{
			MaxSpeed = 500.0f;
			SpeedMultiplier = 2.0f;
			UE_LOG(LogTemp, Warning, TEXT("두 버튼 번갈아 눌림"));
		}
		// 번갈아 누르지 않았을 때 기본 속도로 설정
		else
		{
			MaxSpeed = 250.0f;
			SpeedMultiplier = 2.0f;
			UE_LOG(LogTemp, Warning, TEXT("한 버튼만 눌림 또는 연타"));
		}

		// 마지막 눌린 버튼을 현재 버튼으로 업데이트
		LastButtonPressed = CurrentButton;

		// 속도 적용
		IncreaseSpeed();
	}
	else
	{
		// CheatMode인 경우 최대 속도와 증가 속도를 CheatMode 기준으로 설정
		MaxSpeed = 800.0f;
		SpeedMultiplier = 2.0f;
		TESTIncreaseSpeed();
	}
}

void AMProject_Character::IncreaseSpeed()
{
	// SpeedMultiplier를 적용하여 속도를 설정
	CurrentSpeed = FMath::Clamp(CurrentSpeed + (ClickDistance * SpeedMultiplier), 0.0f, MaxSpeed * SpeedMultiplier);
}

void AMProject_Character::ResetButtonState()
{
	bRedButtonPressed = false;
	bGreenButtonPressed = false;
	bBlueButtonPressed = false;
}

void AMProject_Character::OnLapComplete()
{
	UE_LOG(LogTemp, Log, TEXT("도착했습니다! 3바퀴 완료"));
	m_bGameClear = true;
	OnPlayerClear.Broadcast();
	CurrentSpeed = 0.0f;
}
