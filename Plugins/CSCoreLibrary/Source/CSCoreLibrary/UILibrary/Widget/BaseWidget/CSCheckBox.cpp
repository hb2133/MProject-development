// Fill out your copyright notice in the Description page of Project Settings.


#include "UILibrary/Widget/BaseWidget/CSCheckBox.h"

#include "CSCheckBox.h"
#include "UILibrary/Widget/BaseSlate/SCSCheckBox.h"
#include "CSRadioGroup.h"
#include "CSWidgetSwitcher.h"

UCSCheckBox::UCSCheckBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_widgetSwitcher(nullptr)
{
}

TSharedRef<SWidget> UCSCheckBox::RebuildWidget()
{
	MyCheckbox = SNew(SCSCheckBox)
		.OnCheckStateChanged(BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, SlateOnStateChangedCallback))
		.Style(&GetWidgetStyle())
		.HAlign(HorizontalAlignment);

	if (GetChildrenCount() > 0)
	{
		MyCheckbox->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}

	// MouseCapture 디폴트값 : false
	SetEnableMouseCapture(false);

	return MyCheckbox.ToSharedRef();
}

void UCSCheckBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdateSwitcher(GetCheckedState());
}

void UCSCheckBox::PostLoad()
{
	Super::PostLoad();

	if (this->HasAnyChildren())
	{
		for (int i = 0; i < this->GetChildrenCount(); ++i)
		{
			m_widgetSwitcher = Cast<UCSWidgetSwitcher>(this->GetChildAt(i));
		}
	}
}

void UCSCheckBox::SetRadioGroupBroadcastCheckedState(ECheckBoxState NewState, bool Broadcast /* = false */)
{
	SetCheckedState(NewState);
	UpdateSwitcher(NewState);
	if (IsVisible() == true)
	{
		SetVisibility(NewState == ECheckBoxState::Checked ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);
	}

	if (Broadcast == true)
	{
		const bool bWanCSToBeChecked = NewState != ECheckBoxState::Unchecked;
		OnCheckStateChanged.Broadcast(bWanCSToBeChecked);
		OnStateChanged.Broadcast(this, NewState);
	}
}

void UCSCheckBox::SetBroadcastCheckedState(ECheckBoxState NewState)
{
	SetCheckedState(NewState);
	UpdateSwitcher(NewState);
	const bool bWanCSToBeChecked = NewState != ECheckBoxState::Unchecked;
	OnCheckStateChanged.Broadcast(bWanCSToBeChecked);
	OnStateChanged.Broadcast(this, NewState);
}

void UCSCheckBox::SetEnableMouseCapture(bool bValue)
{
	if (SCSCheckBox* pCheckBox = static_cast<SCSCheckBox*>(MyCheckbox.Get()))
	{
		pCheckBox->SetEnableMouseCapture(bValue);
	}
}

void UCSCheckBox::SlateOnStateChangedCallback(ECheckBoxState NewState)
{
	//CBUIUtils::OnClicked(this);

	SetCheckedState(NewState);
	UpdateSwitcher(NewState);

	//@TODO: Choosing to treat Undetermined as Checked
	const bool bWanCSToBeChecked = NewState != ECheckBoxState::Unchecked;
	OnCheckStateChanged.Broadcast(bWanCSToBeChecked);
	OnStateChanged.Broadcast(this, NewState);
}

void UCSCheckBox::UpdateSwitcher(ECheckBoxState newState)
{
	if (m_widgetSwitcher == nullptr)
		return;

	if (m_widgetSwitcher->GetChildrenCount() > (int)newState)
	{
		m_widgetSwitcher->SetActiveWidgetIndex((int)newState);
	}
}