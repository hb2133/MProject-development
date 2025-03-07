// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "UILibrary/Widget/CSWidgetUtils.h"
#include "CSScrollBox.generated.h"

class UCSUserWidgetBase;
class UCSWidgetSlot;

UCLASS()
class CSCORELIBRARY_API UCSScrollBox : public UScrollBox
{
	GENERATED_BODY()

	friend class UCSWidgetScrollBox;
	
public:
	UPROPERTY(EditAnywhere, Category = "CSUI|CSScrollBox")
	int32 SlotPadding;
	UPROPERTY(EditAnywhere, Category = "CSUI|CSScrollBox")
	int32 SlotSizeX;
	UPROPERTY(EditAnywhere, Category = "CSUI|CSScrollBox")
	int32 SlotSizeY;

public:
	UCSScrollBox();
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;

public:
	virtual void PostLoad() override;
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

	void ScrollMoveToSlot(int index, bool bAnimation = true);
	
	void SetOrientation(EOrientation eOrientation);
	void SetScrollBarVisibility(EVisibility InVisibility);
	void SetSlotPadding(FMargin InPadding);

	void SetSlotSelectedType(ESelectTypeEnum ChildSelectType);
	void SetChildClickEvent(UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget);
	
	bool RemoveChild(UCSWidgetSlot* _pChild, bool _bDestorySlot);
	
	UCSWidgetSlot* AddChild(UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget = nullptr, bool _bFill = false, bool _bExcptAddToSuper = false);
	UCSWidgetSlot* InsertChild(int32 _nInsertIdx, UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget, bool _bRecalcSlotIndex,
							bool _bFill = false, bool _bExceptAddToSuper = false, bool _bFixScrollView = false);
	bool RemoveChildFromSlot(UCSWidgetSlot* _pInChild, bool _bDestroySlot);
	void RemoveChildAll(bool _bClearChildren, bool _bDestorySlot = true);

	UCSWidgetSlot* FindChildFromIndex(int32 _nIdx);
	TArray<UCSWidgetSlot*>& GetWidgetChildren();
	
	virtual bool IsSelectedChild(UCSWidgetSlot* _pChild);
	virtual bool IsSelectedChild(int _nIdx);
	virtual bool AddSelectedChild(UCSWidgetSlot* _pChild);
	virtual bool AddSelectedChild(int _nIdx);
	virtual bool DelSelectedChild(UCSWidgetSlot* _pChild, bool _bSetDeSelectState = true);
	virtual bool DelSelectedChildAll(bool _bSetDeSelectState);
	virtual ESelectTypeEnum GetSelectType() const {return m_SlotSelectType;};
	virtual UCSWidgetSlot* GetFirstSelectedChild();
	bool CanAddSelected(UCSWidgetSlot* _pChild);
	

//public:
//	virtual void OnChildItemClicked(UCSWidgetSlot* _pChildSlot) override;
//	virtual void OnChildItemPressed(UCSWidgetSlot* _pChildSlot) override;
//	virtual void OnChildItemReleased(UCSWidgetSlot* _pChildSlot) override;

protected:
	UPROPERTY() TArray<UCSWidgetSlot*> m_arrWidgetChildren;
	UPROPERTY() TArray<UCSWidgetSlot*> m_arrSelectedChildren;
	ESelectTypeEnum m_SlotSelectType = ESelectTypeEnum::None;
	
};
