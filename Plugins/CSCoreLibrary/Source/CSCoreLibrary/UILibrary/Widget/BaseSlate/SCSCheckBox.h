// Copyright 1998-2015 Epic Games, Inc. All RighCS Reserved.

#pragma once

#include "SlateSound.h"
#include "SCheckBox.h"

class CSCORELIBRARY_API SCSCheckBox : public SCheckBox
{

public:
	void SetEnableMouseCapture(bool bValue);

public:
	void SetHoveredSound(TOptional<FSlateSound> slateSound);
	void SetCheckedSound(TOptional<FSlateSound> slateSound);
	void SetUncheckedSound(TOptional<FSlateSound> slateSound);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

	virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;

private:
	bool m_bMouseCaptureEnabled = true;

};