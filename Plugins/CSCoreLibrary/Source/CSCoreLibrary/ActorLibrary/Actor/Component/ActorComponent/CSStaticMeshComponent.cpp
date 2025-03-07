// Fill out your copyright notice in the Description page of Project Settings.


#include "CSStaticMeshComponent.h"

UCSStaticMeshComponent::UCSStaticMeshComponent()
{
	PrimaryComponentTick.bCanEverTick=true;
}

void UCSStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
