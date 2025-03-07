// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SConstraintCanvas.h"

class UWidget;

class CSCORELIBRARY_API SCSConstraintCanvas : public SConstraintCanvas
{
public:
	SCSConstraintCanvas();

public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Behavior", AdvancedDisplay )
	UWidget* ToolTipWidget;

public:
	virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;

	/**
	* Gets the widget's color.
	*/
	FLinearColor GetColorAndOpacity() const
	{
		return ColorAndOpacity;
	}

	/**
	* Sets the widget's color.
	*
	* @param InColorAndOpacity The ColorAndOpacity to be applied to this widget and all its contents.
	*/
	void SetColorAndOpacity( const FLinearColor& InColorAndOpacity )
	{
		ColorAndOpacity = InColorAndOpacity;
	}

	void SetAddLayerID( int32 InLayerID );
	int32 GetAddLayerID() const;

private:
	typedef TArray<bool, TInlineAllocator<16>> FArrangedChildLayers;
	void CustomArrangeLayeredChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren, FArrangedChildLayers& ArrangedChildLayers ) const;

protected:
	int32 AddLayerID;
	FLinearColor ColorAndOpacity;
};