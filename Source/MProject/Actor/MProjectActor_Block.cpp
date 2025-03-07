#include "MProjectActor_Block.h"

#include "CoreLibrary/Manager/CSFileManager.h"
#include "Kismet/KismetMaterialLibrary.h"

AMProjectActor_Block::AMProjectActor_Block()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	TArray<FVector> Positions = {
		FVector(100, 0, 0),
		FVector(100, -100, 0),
		FVector(100, 100, 0),
		FVector(0, -100, 0),
		FVector(0, 0, 0),
		FVector(0, 100, 0),
		FVector(-100, 0, 0),
		FVector(-100, 100, 0),
		FVector(-100, -100, 0)
	};
	
	for (int32 i = 0; i < 9; ++i)
	{
		UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("StaticMeshComponent_%d"), i));
		MeshComponent->SetupAttachment(DefaultSceneRoot);
		MeshComponent->SetRelativeLocation(Positions[i]);
		MeshComponents.Add(MeshComponent);
	}
}

void AMProjectActor_Block::BeginPlay()
{
	Super::BeginPlay();

	switch (BlockType)
	{
	case EBlockType::Block1:
		this->Tags.Add(FName("Block1"));
		Health = 3;
		if(UMaterialInstance* pMaterial = g_FileMgr->LoadObject<UMaterialInstance>(nResourceType::General,"MI_Mud_Roots"))
		{
			if(UMaterialInstanceDynamic* pMID = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),pMaterial))
			{
				for(int32 i = 0; i < 9; ++i)
				{
					MeshComponents[i]->SetMaterial(0,pMID);
				}
			}
		}
		break;
	case EBlockType::Block2:
		this->Tags.Add(FName("Block2"));
		Health = 6;
		if(UMaterialInstance* pMaterial = g_FileMgr->LoadObject<UMaterialInstance>(nResourceType::General,"Vol_10_Stone_3_Inst"))
		{
			if(UMaterialInstanceDynamic* pMID = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),pMaterial))
			{
				for(int32 i = 0; i < 9; ++i)
				{
					MeshComponents[i]->SetMaterial(0,pMID);
				}
			}
		}
		break;
	case EBlockType::Block3:
		this->Tags.Add(FName("Block3"));
		Health = 9;
		if(UMaterialInstance* pMaterial = g_FileMgr->LoadObject<UMaterialInstance>(nResourceType::General,"Vol_23_Mix_1_Inst"))
		{
			if(UMaterialInstanceDynamic* pMID = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),pMaterial))
			{
				for(int32 i = 0; i < 9; ++i)
				{
					MeshComponents[i]->SetMaterial(0,pMID);
				}
			}
		}
		break;
	default:
		Health = 3;
		break;
	}
}

void AMProjectActor_Block::Tick(float _dt)
{
	Super::Tick(_dt);
}

void AMProjectActor_Block::ReduceHealth()
{
	Health--;
	
	UE_LOG(LogTemp,Log,TEXT("%d"),Health);

	if (Health <= 0)
	{
		Destroy();
	}
}

int32 AMProjectActor_Block::GetBlockHealth()
{
	return Health;
}
