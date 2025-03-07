// Fill out your copyright notice in the Description page of Project Settings.


#include "CSImage.h"

#include "PaperSprite.h"
#include "UILibrary/Widget/CSUIUtils.h"

void UCSImage::SetBrushFromTextureName(FString& strTextureName)
{
	if(UTexture2D* pTexture = CSUIUtils::LoadTexture(strTextureName))
	{
		SetBrushFromTexture(pTexture);
	}	
}

void UCSImage::SetBrushFromSpriteName(const FString& strSpriteName, bool bMatchSize)
{
	if(UPaperSprite* pSprite = CSUIUtils::LoadSprite(strSpriteName))
	{
		
		if(bMatchSize)
		{
			FVector2D vecSize = FVector2D(pSprite->GetSlateAtlasData().GetSourceDimensions().X,pSprite->GetSlateAtlasData().GetSourceDimensions().Y);
			SetDesiredSizeOverride(vecSize);	
		}
		SetBrushResourceObject(pSprite);
		
	}
		
}
