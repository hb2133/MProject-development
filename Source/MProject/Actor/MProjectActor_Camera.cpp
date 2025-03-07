#include "MProjectActor_Camera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

AMProjectActor_Camera::AMProjectActor_Camera()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SetRootComponent(CameraComponent);
}

void AMProjectActor_Camera::BeginPlay()
{
	Super::BeginPlay();
}

void AMProjectActor_Camera::Tick(float _dt)
{
	Super::Tick(_dt);

	// DefaultPawn의 위치를 가져옴
	APawn* DefaultPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (DefaultPawn)
	{
		// DefaultPawn의 위치를 바라보도록 카메라의 회전 설정
		FVector PawnLocation = DefaultPawn->GetActorLocation();
		FVector CameraLocation = CameraComponent->GetComponentLocation();

		// 카메라가 DefaultPawn을 바라보는 방향 계산
		FRotator LookAtRotation = (PawnLocation - CameraLocation).Rotation();
		CameraComponent->SetWorldRotation(LookAtRotation);
	}
}
