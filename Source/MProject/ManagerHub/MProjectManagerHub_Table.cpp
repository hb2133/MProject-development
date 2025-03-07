// Fill out your copyright notice in the Description page of Project Settings.

#include "MProjectManagerHub_Table.h"

#include "ActorLibrary/DataTable/DataManager/CSActorRecordMgr.h"
//#include "DataTable/DataManager/BCChatBotRecordMgr.h"

#include "MProject/DataTable/DataManager/MPCustomizeRecordMgr.h"
#include "MProject/DataTable/DataManager/MPCustomizeSpriteRecordMgr.h"
#include "TableLibrary//DataTable/DataManager/CSSkyRecordMgr.h"

#include "TableLibrary/DataTable/DataManager/CSDefineRecordMgr.h"
#include "TableLibrary/DataTable/DataManager/MCStringTableDataRecordMgr.h"
#include "TableLibrary/Manager/CSMiniMapMgr.h"
#include "UILibrary/DataTable/DataManager/CSPopupRecordMgr.h"
#include "UILibrary/DataTable/DataManager/CSUIDataRecordMgr.h"

using namespace ManagerHub;
using namespace ManagerHub::Table;

void MProjectManagerHub_Table::InitManagers()
{
	//:: Global
	Init(EManageState::eGlobalInit, ETBManagerID::eActorDataRecordMgr, g_ActorRecordMgr);
	Init(EManageState::eGlobalInit, ETBManagerID::eDefineRecordMgr, g_CSDefineRecordMgr);
	Init(EManageState::eGlobalInit, ETBManagerID::eUIDataRecordMgr, g_UIDataRecordMgr);
	Init(EManageState::eGlobalInit, ETBManagerID::eStringTableRecordMgr,g_StringTableDataRecordMgr);
	Init(EManageState::eGlobalInit, ETBManagerID::ePopupRecordMgr,g_PopupRecordMgr);
	Init(EManageState::eGlobalInit, ETBManagerID::eMPCustomizeRecordMgr, g_MPCustomizeRecordMgr);
	Init(EManageState::eGlobalInit, ETBManagerID::eMPSpriteRecordMgr, g_MPCustomizeSpriteRecordMgr);
}