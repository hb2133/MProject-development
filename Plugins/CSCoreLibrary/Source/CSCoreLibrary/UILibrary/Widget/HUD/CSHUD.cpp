// Fill out your copyright notice in the Description page of Project Settings.


#include "UILibrary/Widget/HUD/CSHUD.h"
#include "UILibrary/Manager/CSUIMgr.h"
#include "CoreLibrary/GameInstance/CSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "CoreLibrary/DataTable/DataManager/CSLevelManageTypeRecordMgr.h"
#include "CoreLibrary/DataTable/DataRecord/CSLevelManageTypeRecord.h"

void ACSHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UCSGameInstance* _pGameInst = ::Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (CSLevelManageTypeRecord* _pRecord = g_LevelManageTypeMgr->FindRecord(_pGameInst->GetCurLevelName()))
		{
			CreateWidgetPanels();
			nUIPanelType::en _pFirstPanelType = nUIPanelType::GetEnum(_pRecord->m_strFirstWidget.ToString(), false);

			if (g_UIMgrValid)
				g_UIMgr->ShowUIPanel(_pFirstPanelType);
		}
	}
}
