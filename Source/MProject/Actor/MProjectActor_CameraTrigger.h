#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/CSActor.h"
#include "Camera/CameraActor.h"
#include "MProjectActor_CameraTrigger.generated.h"

class UBoxComponent;
class AMProjectActor_Camera;
UCLASS()
class MPROJECT_API AMProjectActor_CameraTrigger : public ACSActor
{
	GENERATED_BODY()
public:
	AMProjectActor_CameraTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option")
	TArray<AMProjectActor_Camera*> CameraArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option")
	int32 Number;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _dt) override;

	UPROPERTY(Category=COLLISION_GIZMO, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox;


public:
	UFUNCTION()
	void TriggerMoistureBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerMoistureEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
