// Copyright 1998-2015 Epic Games, Inc. All RighCS Reserved.

#include "SCSCheckBox.h"
//#include "GameMgr/CBWidgetTouchStateMgr.h"

void SCSCheckBox::SetEnableMouseCapture(bool bValue)
{
	m_bMouseCaptureEnabled = bValue;
}

void SCSCheckBox::SetHoveredSound(TOptional<FSlateSound> slateSound)
{
	HoveredSound = slateSound.Get(Style->HoveredSlateSound);
}

void SCSCheckBox::SetCheckedSound(TOptional<FSlateSound> slateSound)
{
	CheckedSound = slateSound.Get(Style->CheckedSlateSound);
}

void SCSCheckBox::SetUncheckedSound(TOptional<FSlateSound> slateSound)
{
	UncheckedSound = slateSound.Get(Style->UncheckedSlateSound);
}

FReply SCSCheckBox::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//g_WidgetTouchStateMgr.SetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnMouseButtonDown, MouseEvent);

	FReply reply = SCheckBox::OnMouseButtonDown(MyGeometry, MouseEvent);

	if (m_bMouseCaptureEnabled == false)
	{
		reply.ReleaseMouseCapture();
	}

	return reply;
}

FReply SCSCheckBox::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//g_WidgetTouchStateMgr.ResetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnMouseButtonUp, MouseEvent);

	FReply reply = FReply::Unhandled();

	if (bIsPressed == true && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton))
	{
		if(MouseEvent.IsTouchEvent())
		{
			// EButtonTouchMethod::Type origClick = TouchMethod;
			//
			// TouchMethod = EButtonTouchMethod::DownAndUp;
			// if(GEngine)
			// 	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("Touch"));
			// reply = SCheckBox::OnMouseButtonUp(MyGeometry, MouseEvent);
			//
			// TouchMethod = origClick;
			ToggleCheckedState();
			const ECheckBoxState State = IsCheckboxChecked.Get();
			if(State == ECheckBoxState::Checked)
			{
				PlayCheckedSound();
			}
			else if(State == ECheckBoxState::Unchecked)
			{
				PlayUncheckedSound();
			}
			bIsPressed = false;
			return FReply::Unhandled();
		}
		
		{
			//�̺�Ʈ�� ������ ȣ���ϰ� �ϱ� ���� ó��. ���߿� ���� ������Ʈ �Ǹ� �ű⿡ �°� �����ؾ� �� ���� �ִ�.
			EButtonClickMethod::Type origClickMethod = ClickMethod;
			if (m_bMouseCaptureEnabled == false)
			{
				ClickMethod = EButtonClickMethod::MouseUp;
			}
			reply = SCheckBox::OnMouseButtonUp(MyGeometry, MouseEvent);

			if (m_bMouseCaptureEnabled == false)
			{
				ClickMethod = origClickMethod;
			}
		}
	}
	return FReply::Unhandled();
}

void SCSCheckBox::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//g_WidgetTouchStateMgr.SetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnMouseEnter, MouseEvent);

	SCheckBox::OnMouseEnter(MyGeometry, MouseEvent);
}

void SCSCheckBox::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	//g_WidgetTouchStateMgr.ResetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnMouseLeave, MouseEvent);

	SCheckBox::OnMouseLeave(MouseEvent);
}

FReply SCSCheckBox::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	//g_WidgetTouchStateMgr.SetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnTouchStarted, InTouchEvent);

	return SCheckBox::OnTouchStarted(MyGeometry, InTouchEvent);
}

FReply SCSCheckBox::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	//g_WidgetTouchStateMgr.SetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnTouchMoved, InTouchEvent);

	return SCheckBox::OnTouchMoved(MyGeometry, InTouchEvent);
}

FReply SCSCheckBox::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	//g_WidgetTouchStateMgr.ResetTouchState(nWidgetType::CheckBox, nWidgetFunction::OnTouchEnded, InTouchEvent);

	return SCheckBox::OnTouchEnded(MyGeometry, InTouchEvent);
}