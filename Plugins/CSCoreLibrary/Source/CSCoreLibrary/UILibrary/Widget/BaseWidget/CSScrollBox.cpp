// Fill out your copyright notice in the Description page of Project Settings.


#include "CSScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "UILibrary/Widget/WidgetInterface/CSWidgetInterface.h"
#include "UILibrary/Widget/CSWidgetSlot.h"

UCSScrollBox::UCSScrollBox()
{
	m_arrWidgetChildren.Reset();
}

TSharedRef<SWidget> UCSScrollBox::RebuildWidget()
{
	TSharedRef<SWidget> SWidget = Super::RebuildWidget();

	for (int i = 0; i < this->GetChildrenCount(); ++i)
	{
		if (UCSWidgetSlot* _pWidget = ::Cast<UCSWidgetSlot>(this->GetChildAt(i)))
		{
			m_arrWidgetChildren.Add(_pWidget);
		}
	}
	return SWidget;
}

void UCSScrollBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UCSScrollBox::PostLoad()
{
	Super::PostLoad();
}

void UCSScrollBox::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);
}

void UCSScrollBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);
}

void UCSScrollBox::ScrollMoveToSlot(int index, bool bAnimation /*=true*/)
{
	if(Slots.IsValidIndex(index))
	{
		if(UPanelSlot* pPanelSlot = Slots[index])
		{
			ScrollWidgetIntoView(pPanelSlot->Content, bAnimation);	
		}
	}
}

void UCSScrollBox::SetOrientation(EOrientation eOrientation)
{
	if (MyScrollBox.IsValid())
		MyScrollBox->SetOrientation(eOrientation);
}

void UCSScrollBox::SetScrollBarVisibility(EVisibility InVisibility)
{
	if (MyScrollBox.IsValid())
		MyScrollBox->SetScrollBarVisibility(InVisibility);
}

void UCSScrollBox::SetSlotPadding(FMargin InPadding)
{
	for (auto Slot_iter : Slots)
	{
		if (UScrollBoxSlot* TypedSlot = ::Cast<UScrollBoxSlot>(Slot_iter))
			TypedSlot->SetPadding(InPadding);
	}
}

void UCSScrollBox::SetSlotSelectedType(ESelectTypeEnum ChildSelectType)
{
	m_SlotSelectType = ChildSelectType;
}

void UCSScrollBox::SetChildClickEvent(UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget)
{
	if (_pChild)
		_pChild->SetClickEvent(_pEventParentWidget);
}

bool UCSScrollBox::RemoveChild(UCSWidgetSlot* _pChild, bool _bDestorySlot)
{
	if (_pChild == nullptr)
		return false;

	if (this->IsSelectedChild(_pChild) == true)
	{
		this->DelSelectedChild(_pChild, false);
	}

	m_arrWidgetChildren.Remove(_pChild);
	Super::RemoveChild(_pChild);
	_pChild->RemoveClickEvent();

	if (_bDestorySlot)
	{
		_pChild->RemoveFromParent();
		_pChild->ConditionalBeginDestroy();
		_pChild = nullptr;
	}
	return true;
}


UCSWidgetSlot* UCSScrollBox::AddChild(UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget /*= nullptr*/, bool _bFill /*= false*/, bool _bExcptAddToSuper /*= false*/)
{
	if (SlotSizeX > 0)
		_pChild->SetWidth(SlotSizeX);
	
	if (SlotSizeY > 0)
		_pChild->SetHeight(SlotSizeY);
	
	if (_bExcptAddToSuper == false)
		Super::AddChild(_pChild);

	if (UScrollBoxSlot* _pScrollBoxSlot = ::Cast<UScrollBoxSlot>(_pChild->Slot))
	{
		_pScrollBoxSlot->SetPadding(SlotPadding);
		_pScrollBoxSlot->SetHorizontalAlignment(_bFill ? HAlign_Fill : HAlign_Left);
	}

	this->SetChildClickEvent(_pChild, _pEventParentWidget);
	m_arrWidgetChildren.Add(_pChild);

	return _pChild;
}

UCSWidgetSlot* UCSScrollBox::InsertChild(int32 _nInsertIdx, UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget, bool _bRecalcSlotIndex,
	bool _bFill /*= false*/, bool _bExceptAddToSuper /*= false*/, bool _bFixScrollView /*= false*/)
{
	//:: Insert 기능 추후 작업
	return nullptr;
}

bool UCSScrollBox::RemoveChildFromSlot(UCSWidgetSlot* _pInChild, bool _bDestroySlot)
{
	for (int i = 0; i < m_arrWidgetChildren.Num(); ++i)
	{
		UCSWidgetSlot* _pChild = m_arrWidgetChildren[i];
		if (_pInChild == _pChild)
		{
			return this->RemoveChild(_pChild, _bDestroySlot);
		}
	}
	return false;
}

void UCSScrollBox::RemoveChildAll(bool _bClearChildren, bool _bDestorySlot /*= true*/)
{
	this->DelSelectedChildAll(false);

	for (int i = 0; i < m_arrWidgetChildren.Num(); ++i)
	{
		if (UCSWidgetSlot* _pChild = m_arrWidgetChildren[i])
		{
			if (_bDestorySlot)
			{
				_pChild->RemoveFromParent();
				_pChild->ConditionalBeginDestroy();
				_pChild = nullptr;
			}
		}
	}
	m_arrWidgetChildren.Empty();
}

UCSWidgetSlot* UCSScrollBox::FindChildFromIndex(int32 _nIdx)
{
	if (m_arrWidgetChildren.IsValidIndex(_nIdx))
	{
		return m_arrWidgetChildren[_nIdx];
	}
	return nullptr;
}

TArray<UCSWidgetSlot*>& UCSScrollBox::GetWidgetChildren()
{
	return m_arrWidgetChildren;
}

bool UCSScrollBox::IsSelectedChild(UCSWidgetSlot* _pChild)
{
	if (m_SlotSelectType == ESelectTypeEnum::None)
		return false;

	for (int i = 0; i < m_arrSelectedChildren.Num(); ++i)
	{
		if (m_arrSelectedChildren[i] == _pChild)
			return true;
	}
	return false;
}

bool UCSScrollBox::IsSelectedChild(int _nIdx)
{
	if (UCSWidgetSlot* _pWidgetSlot = this->FindChildFromIndex(_nIdx))
		return this->IsSelectedChild(_pWidgetSlot);

	return false;
}

bool UCSScrollBox::AddSelectedChild(UCSWidgetSlot* _pChild)
{
	if (this->CanAddSelected(_pChild) == false)
		return false;

	if(_pChild->GetImageIcon() == true)
		return false;

	switch (m_SlotSelectType)
	{
		case ESelectTypeEnum::Single:
		{
			this->DelSelectedChildAll(true);
		}
		break;
		case ESelectTypeEnum::Multi:
		{
			if (this->IsSelectedChild(_pChild) == true)
			{
				this->DelSelectedChild(_pChild, true);
				return false;
			}
		}
		break;
	}
	m_arrSelectedChildren.Add(_pChild);
	_pChild->SetSelected(true);

	return false;
}

bool UCSScrollBox::AddSelectedChild(int _nIdx)
{
	if (UCSWidgetSlot* _pWidgetSlot = this->FindChildFromIndex(_nIdx))
		return this->AddSelectedChild(_pWidgetSlot);

	return false;
}

bool UCSScrollBox::DelSelectedChild(UCSWidgetSlot* _pChild, bool _bSetDeSelectState /*= true*/)
{
	if (m_SlotSelectType == ESelectTypeEnum::None)
		return false;

	for (int i = 0; i < m_arrSelectedChildren.Num(); ++i)
	{
		if (m_arrSelectedChildren[i] == _pChild)
		{
			if (_bSetDeSelectState == true)
				_pChild->SetSelected(false);
			m_arrSelectedChildren.RemoveAt(i);
			return true;
		}
	}
	return false;
}

bool UCSScrollBox::DelSelectedChildAll(bool _bSetDeSelectState)
{
	for (int i = 0; i < m_arrSelectedChildren.Num(); ++i)
	{
		if (_bSetDeSelectState && this->IsSelectedChild(m_arrSelectedChildren[i]))
			m_arrSelectedChildren[i]->SetSelected(false);
	}
	m_arrSelectedChildren.Reset();

	return false;
}

UCSWidgetSlot* UCSScrollBox::GetFirstSelectedChild()
{
	if(m_arrSelectedChildren.IsValidIndex(0))
		return m_arrSelectedChildren[0];
	
	return nullptr;
}

bool UCSScrollBox::CanAddSelected(UCSWidgetSlot* _pChild)
{
	//:: 선택타입이 none이면 선택불가
	if (m_SlotSelectType == ESelectTypeEnum::None)
		return false;

	//:: 선택타입이 Single인데 이미 선택된 경우
	if (m_SlotSelectType == ESelectTypeEnum::Single)
	{
		if (this->IsSelectedChild(_pChild) == true)
			return false;
	}
	return true;
}

//void UCSScrollBox::OnChildItemClicked(UCSWidgetSlot* _pChildSlot)
//{
//	CSUIShell::OnChildItemClicked(_pChildSlot);
//
//	this->AddSelectedChild(_pChildSlot);
//}
//
//void UCSScrollBox::OnChildItemPressed(UCSWidgetSlot* _pChildSlot)
//{
//	CSUIShell::OnChildItemPressed(_pChildSlot);
//}
//
//void UCSScrollBox::OnChildItemReleased(UCSWidgetSlot* _pChildSlot)
//{
//	CSUIShell::OnChildItemReleased(_pChildSlot);
//}