#include "MProjectActor_Spline.h"
#include "Components/SplineComponent.h"

// Sets default values
AMProjectActor_Spline::AMProjectActor_Spline()
{
	// 스플라인 컴포넌트 생성 및 설정
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

	// 포인트 설정
	SplineComponent->ClearSplinePoints();
	SplineComponent->AddSplinePoint(FVector(0.0f, 0.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(-1000.0f, 0.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(-2000.0f, 150.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(-2750.0f, 1000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(-2750.0f, 2000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(-2000.0f, 2850.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(-1000.0f, 3000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(0.0f, 3000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(1000.0f, 3000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(2000.0f, 2850.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(2750.0f, 2000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(2750.0f, 1000.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(2000.0f, 150.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	SplineComponent->AddSplinePoint(FVector(1000.0f, 0.0f, 0.0f), ESplineCoordinateSpace::Local, true);

	// 스플라인을 선형으로 설정
	for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints(); i++)
	{
		SplineComponent->SetSplinePointType(i, ESplinePointType::Curve);
	}

	// 스플라인 자동 클로즈 기능 활성화
	SplineComponent->SetClosedLoop(true);
}

// Called when the game starts or when spawned
void AMProjectActor_Spline::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMProjectActor_Spline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
