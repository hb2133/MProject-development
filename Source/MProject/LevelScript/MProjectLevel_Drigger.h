// MProjectLevel_Drigger.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MProjectLevel_Drigger.generated.h"

UCLASS()
class MPROJECT_API AMProjectLevel_Drigger : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	AMProjectLevel_Drigger();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
