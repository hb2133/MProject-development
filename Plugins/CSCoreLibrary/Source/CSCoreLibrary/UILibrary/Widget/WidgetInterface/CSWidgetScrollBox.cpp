// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidgetScrollBox.h"
#include "UILibrary/Widget/CSWidgetSlot.h"
#include "UILibrary/Widget/BaseWidget/CSScrollBox.h"

void UCSWidgetScrollBox::InitData()
{
	Super::InitData();

	if (ScrollBox_Base)
	{
		TArray<UCSWidgetSlot*> _arrWidgetSlots = ScrollBox_Base->GetWidgetChildren();
		for (int i = 0; i < _arrWidgetSlots.Num(); ++i)
		{
			if (_arrWidgetSlots[i] != nullptr)
			{
				if(_arrWidgetSlots[i]->m_bSelected)
					ScrollBox_Base->AddSelectedChild(_arrWidgetSlots[i]);
			}
		}
	}
}

void UCSWidgetScrollBox::ReleaseData()
{
	Super::ReleaseData();
}

void UCSWidgetScrollBox::LinkEvent()
{
	Super::LinkEvent();

	// 초기 클릭 이벤트 셋팅 : 슬롯의 부모 위젯으로 설정
	// 이벤트 위젯을 별도로 셋팅하고 싶다면 외부에서 SetClickEvent 함수를 호출해 다시 바인딩해주면 된다.
	if (m_pParentWidget.IsValid())
		this->SetClickEvent(m_pParentWidget.Get());
}

void UCSWidgetScrollBox::UnLinkEvent()
{
	Super::UnLinkEvent();
}

void UCSWidgetScrollBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	if (ScrollBox_Base)
	{
		ScrollBox_Base->SetOrientation(OrientationType);
		ScrollBox_Base->SetScrollBarVisibility(UWidget::ConvertSerializedVisibilityToRuntime(ScrollBarVisibility));
		ScrollBox_Base->SetSlotPadding(SlotPadding);

		ScrollBox_Base->SetSlotSelectedType(ChildSelectType);
	}
	
}

void UCSWidgetScrollBox::OnReceiveSlotSelectedByChild(UCSWidgetSlot* _pSlotChild)
{
	Super::OnReceiveSlotSelectedByChild(_pSlotChild);

	if (ScrollBox_Base)
		ScrollBox_Base->AddSelectedChild(_pSlotChild);
}

void UCSWidgetScrollBox::OnReceiveSlotSelectedByIndex(int32 _nSlotIdx)
{
	Super::OnReceiveSlotSelectedByIndex(_nSlotIdx);

	if (ScrollBox_Base)
		ScrollBox_Base->AddSelectedChild(_nSlotIdx);
}

void UCSWidgetScrollBox::SetClickEvent(UCSUserWidgetBase* _pEventParentWidget)
{
	if (_pEventParentWidget == nullptr)
		return;

	Super::SetEventParentWidget(_pEventParentWidget);
}

void UCSWidgetScrollBox::RemoveClickEvent()
{

}

UCSWidgetSlot* UCSWidgetScrollBox::AddScrollChild(UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget, bool _bExceptAddToSuber /*= false*/)
{
	if (ScrollBox_Base == nullptr || _pChild == nullptr)
		return nullptr;

	if (_pEventParentWidget != nullptr)
		SetEventParentWidget(_pEventParentWidget);

	_pChild->SetParentWidgetInterfaceSlot(this);	
	return ScrollBox_Base->AddChild(_pChild, this, false, _bExceptAddToSuber);
}

UCSWidgetSlot* UCSWidgetScrollBox::InsertScrollChild(int _nIdx, UCSWidgetSlot* _pChild, UCSUserWidgetBase* _pEventParentWidget, bool _bRecalcSlotIndex /*= false*/,
	bool _bExceptionAddToSuper /*= false*/, bool _bFixScrollView /*= false*/)
{
	//:: Insert 기능 추후 작업
	return nullptr;
}

void UCSWidgetScrollBox::RemoveScrollChildAll(bool _bClearChild, bool _bDestroySlot /*= true*/)
{
	if (ScrollBox_Base)
		ScrollBox_Base->RemoveChildAll(_bClearChild, _bDestroySlot);
}

bool UCSWidgetScrollBox::RemoveScrollChildFromSlot(UCSWidgetSlot* _pInChild, bool _bDestroySlot /*= true*/)
{
	if (ScrollBox_Base == nullptr)
		return false;

	return ScrollBox_Base->RemoveChildFromSlot(_pInChild, _bDestroySlot);
}

UCSWidgetSlot* UCSWidgetScrollBox::FindScrollChildFromIndex(int _nIdx)
{
	if (ScrollBox_Base == nullptr)
		return nullptr;

	return ScrollBox_Base->FindChildFromIndex(_nIdx);
}

TArray<UCSWidgetSlot*> UCSWidgetScrollBox::GetWidgetChildren()
{
	if (ScrollBox_Base == nullptr)
		return TArray<UCSWidgetSlot*>();

	return ScrollBox_Base->GetWidgetChildren();
}

ESelectTypeEnum UCSWidgetScrollBox::GetSelectType()
{
	if (ScrollBox_Base == nullptr)
		return ESelectTypeEnum::None;

	return ScrollBox_Base->GetSelectType();
}

bool UCSWidgetScrollBox::IsSelectedChild(UCSWidgetSlot* pChild)
{
	if(ScrollBox_Base == nullptr)
		return false;
	
	return ScrollBox_Base->IsSelectedChild(pChild);
}

bool UCSWidgetScrollBox::AddSelectedChild(UCSWidgetSlot* pChild)
{
	if(ScrollBox_Base == nullptr)
		return false;
	
	return ScrollBox_Base->AddSelectedChild(pChild);
}

bool UCSWidgetScrollBox::AddSelectedChild(int index)
{
	if(ScrollBox_Base == nullptr)
		return false;
	
	return ScrollBox_Base->AddSelectedChild(index);
}

bool UCSWidgetScrollBox::DelSelectedChild(UCSWidgetSlot* pChild)
{
	if(ScrollBox_Base == nullptr)
		return false;
	
	return ScrollBox_Base->DelSelectedChild(pChild);
}

bool UCSWidgetScrollBox::DelSelectedChildAll(bool bSetSelectedState)
{
	if(ScrollBox_Base == nullptr)
		return false;
	
	return ScrollBox_Base->DelSelectedChildAll(bSetSelectedState);
}

bool UCSWidgetScrollBox::CanAddSelected(UCSWidgetSlot* pChild)
{
	if(ScrollBox_Base == nullptr)
		return false;
	
	return ScrollBox_Base->CanAddSelected(pChild);
}

UCSWidgetSlot* UCSWidgetScrollBox::GetFirstSelectedChild()
{
	if(ScrollBox_Base == nullptr)
		return nullptr;
	
	return ScrollBox_Base->GetFirstSelectedChild();
}

void UCSWidgetScrollBox::SetScrollPos(int32 iIndex)
{
	if(ScrollBox_Base == nullptr)
		return;

	ScrollBox_Base->ScrollMoveToSlot(iIndex);
}

void UCSWidgetScrollBox::OnChildItemClicked(UCSUserWidgetBase* _pChildWidget) 
{
	if (_pChildWidget == nullptr)
		return;

	if (ScrollBox_Base)
	{
		if(UCSWidgetSlot* _pSlotChild = ::Cast<UCSWidgetSlot>(_pChildWidget))
			ScrollBox_Base->AddSelectedChild(_pSlotChild);
	}

	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemClicked(_pChildWidget);
}

void UCSWidgetScrollBox::OnChildItemPressed(UCSUserWidgetBase* _pChildWidget)
{
	if (_pChildWidget == nullptr)
		return;

	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemPressed(_pChildWidget);
}

void UCSWidgetScrollBox::OnChildItemReleased(UCSUserWidgetBase* _pChildWidget)
{
	if (_pChildWidget == nullptr)
		return;

	if (m_pEventParentWidget.IsValid())
		m_pEventParentWidget->OnChildItemReleased(_pChildWidget);
}

