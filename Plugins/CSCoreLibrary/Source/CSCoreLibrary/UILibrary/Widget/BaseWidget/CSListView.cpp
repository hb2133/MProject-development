// Fill out your copyright notice in the Description page of Project Settings.


#include "CSListView.h"

#include "UILibrary/Define/CSDefine_UICommon.h"
#include "UILibrary/Widget/BaseSlate/SCSListView.h"

void UCSListView::RefreshItems()
{
	//CS_IF_NULLPTR_RET(GetNumItems);
	//CS_IF_NULLPTR_RET(OnGetListItem);

	if (!IsDesignTime())
	{
		TArray<UObject*> ListItemDatas;
		const auto NumItems = GetNumItems();
		for (auto i = 0; i < NumItems; ++i)
		{
			ListItemDatas.Emplace(OnGetListItem(i));
		}

		SetListItems(ListItemDatas);
	}
}

void UCSListView::SetScrollbarVisibility(EVisibility InVisibility)
{
	if(MyListView)
		MyListView->SetScrollbarVisibility(InVisibility);
}

void UCSListView::SetEntrySpacing(float InEntrySpacing)
{
	//5.3부터 EntrySpacing 사용X
	InitHorizontalEntrySpacing(InEntrySpacing);
	InitVerticalEntrySpacing(InEntrySpacing);
	//~5.2
	//EntrySpacing = InEntrySpacing;
}

int32 UCSListView::GetSelectedItemIndex() const
{
	return GetIndexForItem(GetSelectedItem());
}

int32 UCSListView::GetItemCount() const
{
	if (GetNumItems)
	{
		return GetNumItems();
	}
	return 0;
}

UUserWidget& UCSListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	UUserWidget& CreatedWidget = Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);

	if (OnCreatedItem)
	{
		OnCreatedItem(Item, &CreatedWidget);
	}
	
	return CreatedWidget;
}

void UCSListView::OnSelectionChangedInternal(NullableItemType FirstSelectedItem)
{
	Super::OnSelectionChangedInternal(FirstSelectedItem);

//	CS_IF_NULLPTR_RET(OnSelectionChangedItem);

	const TArray<UObject*>& CurListItems = GetListItems();
	for (auto i = 0; i < CurListItems.Num(); ++i)
	{
		const auto CurEntry = GetEntryWidgetFromItem(CurListItems[i]);
		OnSelectionChangedItem(FirstSelectedItem == CurListItems[i], i, CurEntry);
	}
}

TSharedRef<STableViewBase> UCSListView::RebuildListWidget()
{
	auto SlateListView = ConstructListView<SCSListView>();

	if (ScrollbarVisibility == ESlateVisibility::Visible)
	{
		SlateListView->SetScrollbarVisibility(EVisibility::Visible);
	}
	else if (ScrollbarVisibility == ESlateVisibility::Collapsed)
	{
		SlateListView->SetScrollbarVisibility(EVisibility::Collapsed);
	}
	else if (ScrollbarVisibility == ESlateVisibility::SelfHitTestInvisible)
	{
		SlateListView->SetScrollbarVisibility(EVisibility::SelfHitTestInvisible);
	}
	else if (ScrollbarVisibility == ESlateVisibility::HitTestInvisible)
	{
		SlateListView->SetScrollbarVisibility(EVisibility::HitTestInvisible);
	}
	return SlateListView;
	
}
