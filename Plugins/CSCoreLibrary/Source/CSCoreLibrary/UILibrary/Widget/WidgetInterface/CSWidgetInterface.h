// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "UILibrary/Widget/CSWidgetSlot.h"
#include "UILibrary/Widget/CSWidgetUtils.h"
#include "CSWidgetInterface.generated.h"

DECLARE_EVENT_OneParam(UCSWidgetInterface, SlotSelectEventByChild, UCSWidgetSlot*);
DECLARE_EVENT_OneParam(UCSWidgetInterface, SlotSelectEventByIndex, int32);

UCLASS()
class CSCORELIBRARY_API UCSWidgetInterface : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetInterface")
	ESelectTypeEnum ChildSelectType = ESelectTypeEnum::None;

public:
	SlotSelectEventByChild& OnSlotSelectEventByChild() { return m_SlotSelectEventByChild; }
	SlotSelectEventByIndex& OnSlotSelectEventByIndex() { return m_SlotSelectEventByIndex; }

private:
	SlotSelectEventByChild m_SlotSelectEventByChild;
	SlotSelectEventByIndex m_SlotSelectEventByIndex;

public:
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;

public:
	virtual void OnReceiveSlotSelectedByChild(UCSWidgetSlot* _pSlotChild) {}
	virtual void OnReceiveSlotSelectedByIndex(int32 _nSlotIdx) {}

protected:
	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) override;
	virtual void OnChildItemPressed(UCSUserWidgetBase* _pChildWidget) override;
	virtual void OnChildItemReleased(UCSUserWidgetBase* _pChildWidget) override;
};
