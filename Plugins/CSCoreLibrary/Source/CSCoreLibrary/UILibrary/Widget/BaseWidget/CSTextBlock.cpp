// Fill out your copyright notice in the Description page of Project Settings.


#include "CSTextBlock.h"

#include "TableLibrary/DataTable/DataManager/MCStringTableDataRecordMgr.h"
#include "TableLibrary/Manager/CSTableMgr.h"


TSharedRef<SWidget> UCSTextBlock::RebuildWidget()
{
	// FString _strText = this->GetText().ToString();
	// FString _strChangeText = "";
	// if(g_TableMgrValid)
	// {
	// 	if(g_TableMgr->GeteLocalType() == nLocalType::EN)
	// 	{
	// 		for(MCStringTableDetailRecord* pRecord:g_TableMgr->GetarrStringTableRecord())
	// 		{
	// 			if(pRecord->m_strKO == _strText && _strText != "")
	// 			{
	// 				_strChangeText = pRecord->m_strEN;
	//

	this->SetText(GetText());
	
	
	return Super::RebuildWidget();
}

void UCSTextBlock::SetText(FText InText)
{
	if(g_TableMgrValid)
	{
		Super::SetText(ChangeText(g_TableMgr->GeteLocalType(),InText));
	}
	else
	{
		Super::SetText(InText);
	}
}

FText UCSTextBlock::ChangeText(nLocalType::en _elocalType,FText InText)
{
	m_strText = InText.ToString();
	m_strChangeText = "";
	if(m_strTid != "")
	{
		if(MCStringTableDetailRecord* pRecord = g_StringTableDataRecordMgr->FindRecord(m_strTid.ToString()))
		{
			switch (_elocalType)
			{
			case nLocalType::KO:
				{
					if(m_strText == pRecord->m_strEN)
					{
						m_strChangeText = pRecord->m_strKO;
						return FText::FromString(m_strChangeText);
					}
					if(m_strText != pRecord->m_strKO)
					{
						m_strTid =  "";
						return RefreshTid();
					}
				}break;
			case nLocalType::EN:
				{
					if(m_strText == pRecord->m_strKO)
					{
						m_strChangeText = pRecord->m_strEN;
						return FText::FromString(m_strChangeText);
					}
					if(m_strText != pRecord->m_strEN)
					{
						m_strTid =  "";
						return RefreshTid();
					}
				}break;
			default:
				break;
			}
		}
	}
	else
	{
		if(g_TableMgrValid)
		{
			for(MCStringTableDetailRecord* pRecord:g_TableMgr->GetarrStringTableRecord())
			{
				if(pRecord->m_strKO == m_strText && m_strText != "")
				{
					m_strTid = pRecord->m_strTid;
					g_TableMgr->LocalChange.AddUObject(this,&UCSTextBlock::ChangeLocal);
					if(g_TableMgr->GeteLocalType() != nLocalType::KO)
					{
						m_strText = pRecord->m_strEN;
						return FText::FromString(m_strText);
					}
					break;
				}
			}
		}
	}
	return InText;
}

void UCSTextBlock::ChangeLocal(nLocalType::en _elocalType)
{
	SetText(GetText());
}

FText UCSTextBlock::RefreshTid()
{
	for(MCStringTableDetailRecord* pRecord:g_TableMgr->GetarrStringTableRecord())
	{
		if(pRecord->m_strKO == m_strText && m_strText != "")
		{
			m_strTid = pRecord->m_strTid;
			return ChangeText(g_TableMgr->GeteLocalType(),FText::FromString(m_strText));

		}
		if(pRecord->m_strEN == m_strText && m_strText != "")
		{
			m_strTid = pRecord->m_strTid;
			return ChangeText(g_TableMgr->GeteLocalType(),FText::FromString(m_strText));

		}
	}
	return FText::FromString(m_strText);
}
