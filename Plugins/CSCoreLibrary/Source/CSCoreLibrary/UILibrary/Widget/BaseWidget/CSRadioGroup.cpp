// Fill out your copyright notice in the Description page of Project Settings.


#include "UILibrary/Widget/BaseWidget/CSRadioGroup.h"

// Fill out your copyright notice in the Description page of Project Settings.

#include "UILibrary/Widget/BaseSlate/SCSConstraintCanvas.h"
#include "Components/CanvasPanelSlot.h"

#include "CSRadioGroup.h"

#define LOCTEXT_NAMESPACE "UMG"

UCSRadioGroup::UCSRadioGroup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UCSRadioGroup::RebuildWidget()
{
	MyCanvas = SNew(SCSConstraintCanvas);

	for (UPanelSlot* pSlot : Slots)
	{
		if (UCanvasPanelSlot* TypedSlot = Cast<UCanvasPanelSlot>(pSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyCanvas.ToSharedRef());
		}

		if (UCSCheckBox* TypedContent = Cast< UCSCheckBox >(pSlot->Content))
		{
			TypedContent->OnStateChanged.AddDynamic(this, &UCSRadioGroup::SlateOnChildCheckStateChangedCallback);
		}
	}

	return MyCanvas.ToSharedRef();
}

void UCSRadioGroup::SetChecked(int32 index, bool broadcast /*= false*/, bool allUnChecked /*= false*/)
{
	int count = Slots.Num();
	if (count <= 0 || count <= index || index < 0)
		return;

	if (allUnChecked == true)
	{
		this->AllUnChecked();
	}

	if (UCSCheckBox* TypedContent = Cast<UCSCheckBox>(Slots[index]->Content))
	{
		if (TypedContent->GetIsEnabled() == true && TypedContent->GetVisibility() != ESlateVisibility::Hidden)
		{
			TypedContent->SetRadioGroupBroadcastCheckedState(ECheckBoxState::Checked, broadcast);
		}
	}
}

void UCSRadioGroup::SetChecked(UCSCheckBox* checkBox, bool broadcast /*= false*/, bool allUnChecked /*= false*/)
{
	if (allUnChecked == true)
	{
		this->AllUnChecked();
	}

	for (UPanelSlot* pSlot : Slots)
	{
		if (UCSCheckBox* TypedContent = Cast<UCSCheckBox>(pSlot->Content))
		{
			if (TypedContent->GetIsEnabled() == false)
				continue;

			if (TypedContent->GetVisibility() == ESlateVisibility::Hidden)
				continue;

			if (TypedContent == checkBox)
			{
				TypedContent->SetRadioGroupBroadcastCheckedState(ECheckBoxState::Checked, broadcast);
				return;
			}
		}

	}
}

void UCSRadioGroup::SlateOnChildCheckStateChangedCallback(UCSCheckBox* CheckBox, ECheckBoxState NewState)
{
	if (NewState != ECheckBoxState::Checked)
		return;

	int selectedIndex = -1;
	int loopIndex = -1;
	for (UPanelSlot* pSlot : Slots)
	{
		++loopIndex;

		if (UCSCheckBox* TypedContent = Cast<UCSCheckBox>(pSlot->Content))
		{
			if (TypedContent == CheckBox)
			{
				selectedIndex = loopIndex;

				if (TypedContent->GetIsEnabled() == false)
					continue;

				if (TypedContent->GetVisibility() == ESlateVisibility::Hidden)
					continue;

				TypedContent->SetVisibility(ESlateVisibility::HitTestInvisible);
				continue;
			}
	
			TypedContent->SetRadioGroupBroadcastCheckedState(ECheckBoxState::Unchecked, false);

			if (TypedContent->IsVisible() == true)
				TypedContent->SetVisibility(ESlateVisibility::Visible);
			continue;
		}
	}

	OnChildCheckStateChanged.Broadcast(CheckBox, NewState);
	OnSelectedIndexChanged.Broadcast(selectedIndex);
}

int UCSRadioGroup::GetCheckedSlotIndex()
{
	int index = 0;
	for (UPanelSlot* pSlot : Slots)
	{
		if (UCSCheckBox* TypedContent = Cast<UCSCheckBox>(pSlot->Content))
		{
			if (TypedContent->GetIsEnabled() == false)
				continue;

			if (TypedContent->GetVisibility() == ESlateVisibility::Hidden)
				continue;

			if (TypedContent->GetCheckedState() == ECheckBoxState::Checked)
				return index;
		}

		++index;
	}

	return -1;
}

UCSCheckBox* UCSRadioGroup::GetCheckedSlot()
{
	for (UPanelSlot* pSlot : Slots)
	{
		if (UCSCheckBox* TypedContent = Cast<UCSCheckBox>(pSlot->Content))
		{
			if (TypedContent->GetIsEnabled() == false)
				continue;

			if (TypedContent->GetVisibility() == ESlateVisibility::Hidden)
				continue;

			if (TypedContent->GetCheckedState() == ECheckBoxState::Checked)
				return TypedContent;
		}
	}

	return nullptr;
}

void UCSRadioGroup::AllUnChecked()
{
	UCSCheckBox* pCheckBox = nullptr;
	for (int i = 0; i < GetChildrenCount(); ++i)
	{
		pCheckBox = Cast<UCSCheckBox>(GetChildAt(i));
		if (nullptr == pCheckBox)
			continue;

		pCheckBox->SetRadioGroupBroadcastCheckedState(ECheckBoxState::Unchecked);
	}
}

int UCSRadioGroup::GetCheckedIndex()
{
	int index = 0;
	for (UPanelSlot* pSlot : Slots)
	{
		if (UCSCheckBox* TypedContent = Cast<UCSCheckBox>(pSlot->Content))
		{
			if (TypedContent->GetIsEnabled() && TypedContent->IsVisible() && TypedContent->GetCheckedState() == ECheckBoxState::Checked)
				return index;
		}

		++index;
	}

	return -1;
}

#undef LOCTEXT_NAMESPACE