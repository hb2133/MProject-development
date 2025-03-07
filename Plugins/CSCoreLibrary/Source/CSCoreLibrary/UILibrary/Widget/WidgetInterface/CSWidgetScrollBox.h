// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/WidgetInterface/CSWidgetInterface.h"
#include "CSWidgetScrollBox.generated.h"

class UCSScrollBox;
class UCSUserWidgetBase;
class UCSWidgetSlot;

UCLASS()
class CSCORELIBRARY_API UCSWidgetScrollBox : public UCSWidgetInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidgetOptional))
	UCSScrollBox* ScrollBox_Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidget_ScrollBox")
	TEnumAsByte <EOrientation> OrientationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidget_ScrollBox")
	ESlateVisibility ScrollBarVisibility = ESlateVisibility::Visible;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidget_ScrollBox")
	FMargin SlotPadding;

public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	virtual void SynchronizeProperties() override;
public:
	virtual UCSWidgetSlot* AddScrollChild(UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget, bool _bExceptAddToSuber = false);
	virtual UCSWidgetSlot* InsertScrollChild(int _nIdx, UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget, bool _bRecalcSlotIndex = false,
		bool _bExceptionAddToSuper = false, bool _bFixScrollView = false);
	virtual void RemoveScrollChildAll(bool _bClearChild, bool _bDestroySlot = true);
	virtual bool RemoveScrollChildFromSlot(UCSWidgetSlot* _pInChild, bool _bDestroySlot = true);
	virtual UCSWidgetSlot* FindScrollChildFromIndex(int _nIdx);
	virtual TArray<UCSWidgetSlot*> GetWidgetChildren();

	virtual bool IsSelectedChild(UCSWidgetSlot* pChild);
	virtual bool AddSelectedChild(UCSWidgetSlot* pChild);
	virtual bool AddSelectedChild(int index);
	virtual bool DelSelectedChild(UCSWidgetSlot* pChild);
	virtual bool DelSelectedChildAll(bool bSetSelectedState);
	virtual bool CanAddSelected(UCSWidgetSlot* pChild);	
	virtual void SetScrollPos(int32 iIndex);
	
	void InitSelectedChildren() { DelSelectedChildAll(true); }
	virtual UCSWidgetSlot* GetFirstSelectedChild();
	virtual ESelectTypeEnum GetSelectType();
	
	virtual void OnReceiveSlotSelectedByChild(UCSWidgetSlot* _pSlotChild) override;
	virtual void OnReceiveSlotSelectedByIndex(int32 _nSlotIdx) override;

	virtual void SetClickEvent(UCSUserWidgetBase* _pEventParentWidget) override;
	virtual void RemoveClickEvent() override;
	virtual void OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) override;
	virtual void OnChildItemPressed(UCSUserWidgetBase* _pChildWidget) override;
	virtual void OnChildItemReleased(UCSUserWidgetBase* _pChildWidget) override;

	UCSScrollBox* GetScrollBox() { return ScrollBox_Base;}
};
