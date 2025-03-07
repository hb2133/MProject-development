// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILibrary/Widget/CSUserWidgetBase.h"
#include "UILibrary/Widget/CSWidgetUtils.h"
#include "CSWidgetSlot.generated.h"

class UCSButton;
class UCSTextBlock;
class UCSImage;
//class CSUIShell;

UCLASS()
class CSCORELIBRARY_API UCSWidgetSlot : public UCSUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional)) // 슬롯 버튼 
	UCSButton* SlotButton;					
	UPROPERTY(meta = (BindWidgetOptional)) // 슬롯 버튼 (선택됨)
	UCSButton* SlotButton_Selected;	
	UPROPERTY(meta = (BindWidgetOptional)) // 슬롯 버튼 타이틀
	UCSTextBlock* SlotButton_Text_Title;
	UPROPERTY(meta = (BindWidgetOptional)) // 슬롯 버튼 타이틀(선택됨)
	UCSTextBlock* SlotButton_Text_Title_Selected;
	UPROPERTY(meta = (BindWidgetOptional)) // 슬롯 버튼 이미지
	UCSImage* SlotButton_Image_Icon;
	UPROPERTY(meta = (BindWidgetOptional)) // 슬롯 버튼 이미지(선택됨)
	UCSImage* SlotButton_Image_Icon_Selected;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Slot Selected")
	bool m_bSelected = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Slot Enabled")
	bool m_bEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Slot ImageIcon")
	bool m_bImageIcon = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Text Title")
	FName m_strTextTitle = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Text Title Selected")
	FName m_strTextTitleSelected = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Slot Image")
	FSlateBrush m_Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSWidgetSlot", DisplayName = "Slot Image Selected")
	FSlateBrush m_ImageSelected;
	
public:
	virtual void InitData() override;
	virtual void ReleaseData() override;
	virtual void LinkEvent() override;
	virtual void UnLinkEvent() override;
	virtual void SynchronizeProperties() override;
public:
	virtual void Show(ESlateVisibility visible = ESlateVisibility::SelfHitTestInvisible, float fDelayTime = 0.f, float fFadeTime = 0.f, float fDisplayTime = 0.f);
	virtual void Hide(float fDelatTime = 0.f, float fFadeTime = 0.f);

	virtual void SetClickEvent(UCSUserWidgetBase* _pEventParentWidget);
	virtual void RemoveClickEvent();

	virtual void SetParentWidgetForWidgetTree() override;
	
	void SetParentWidgetInterfaceSlot(UCSUserWidgetBase* _pParentWidget);

public:
	virtual void SetWidth(int32 _nWidth) {}
	virtual void SetHeight(int32 _nHeight) {}

public: // Slot
	virtual void SetSelected(bool _bSelected);
	virtual void SetEnabled(bool _bEnabled);
	virtual void SetImageIcon(bool _bImageIcon);
	void SetButtonEnabled(bool _bEnabled);
	bool GetSelected() { return m_bSelected; }
	bool GetEnabled() { return m_bEnabled; }
	bool GetImageIcon() { return m_bImageIcon; }

	void SetSlotIdx(int32 _nSlotIdx) { m_SlotIdx = _nSlotIdx; }
	int32 GetSlotIdx() { return m_SlotIdx; }
	
	void SetButtonTextTitle(FText text,bool bSelected = false);
	void SetButtonTextTitle(FName text,bool bSelected = false);

private:
	void UpdateVisibleBySelectState(bool _bSelected);

public:
	UFUNCTION() virtual void OnClicked();
	UFUNCTION() virtual void OnPressed();
	UFUNCTION() virtual void OnReleased();
	UFUNCTION() virtual void OnHovered();
	UFUNCTION() virtual void OnUnHovered();

protected:
	int32 m_SlotIdx = 0;
	ESlotParentTypeEnum m_eSlotParentType = ESlotParentTypeEnum::Parent_Normal;

	//TWeakObjectPtr<CSUIShell> m_pParentWidgetInterface = nullptr;
};
