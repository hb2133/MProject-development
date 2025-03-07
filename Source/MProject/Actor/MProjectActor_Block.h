#pragma once

#include "CoreMinimal.h"
#include "ActorLibrary/Actor/CSActor.h"
#include "MProjectActor_Block.generated.h"

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Block1 UMETA(DisplayName = "Block1"),
	Block2 UMETA(DisplayName = "Block2"),
	Block3 UMETA(DisplayName = "Block3")
};

UCLASS()
class MPROJECT_API AMProjectActor_Block : public ACSActor
{
	GENERATED_BODY()
public:
	AMProjectActor_Block();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _dt) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	EBlockType BlockType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block")
	int32 Health;

	void ReduceHealth();
	int32 GetBlockHealth();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block")
	TArray<UStaticMeshComponent*> MeshComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block")
	USceneComponent* DefaultSceneRoot;
};
