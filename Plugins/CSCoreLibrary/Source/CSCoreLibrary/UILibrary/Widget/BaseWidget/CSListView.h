// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListView.h"
#include "CSListView.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSListView : public UListView
{
	GENERATED_BODY()

public:
	void RefreshItems();
	void SetScrollbarVisibility(EVisibility InVisibility);
	void SetEntrySpacing(float InEntrySpacing);

	int32 GetSelectedItemIndex() const;
	int32 GetItemCount() const;
	
public:
	TFunction<int32()> GetNumItems;
	TFunction<void(bool, int32, UUserWidget*)> OnSelectionChangedItem;
	TFunction<void(UObject*, UUserWidget*)> OnCreatedItem;
	TFunction<UObject* (int32)> OnGetListItem;
	
protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;

	virtual void OnSelectionChangedInternal(NullableItemType FirstSelectedItem) override;
	virtual TSharedRef<STableViewBase> RebuildListWidget() override;

protected:
	UPROPERTY(EditAnywhere)
	ESlateVisibility ScrollbarVisibility;
};
