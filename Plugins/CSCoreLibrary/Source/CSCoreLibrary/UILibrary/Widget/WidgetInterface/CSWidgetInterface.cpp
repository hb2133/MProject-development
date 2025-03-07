// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWidgetInterface.h"

void UCSWidgetInterface::LinkEvent()
{
	Super::LinkEvent();

	OnSlotSelectEventByChild().AddUObject(this, &UCSWidgetInterface::OnReceiveSlotSelectedByChild);
	OnSlotSelectEventByIndex().AddUObject(this, &UCSWidgetInterface::OnReceiveSlotSelectedByIndex);
}

void UCSWidgetInterface::UnLinkEvent()
{
	OnSlotSelectEventByChild().RemoveAll(this);
	OnSlotSelectEventByIndex().RemoveAll(this);

	Super::UnLinkEvent();
}

void UCSWidgetInterface::OnChildItemClicked(UCSUserWidgetBase* _pChildWidget)
{
	Super::OnChildItemClicked(_pChildWidget);
}

void UCSWidgetInterface::OnChildItemPressed(UCSUserWidgetBase* _pChildWidget)
{
	Super::OnChildItemPressed(_pChildWidget);
}

void UCSWidgetInterface::OnChildItemReleased(UCSUserWidgetBase* _pChildWidget)
{
	Super::OnChildItemReleased(_pChildWidget);
}
