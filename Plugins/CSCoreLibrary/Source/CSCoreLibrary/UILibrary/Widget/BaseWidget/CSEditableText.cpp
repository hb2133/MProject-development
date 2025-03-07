// Fill out your copyright notice in the Description page of Project Settings.


#include "CSEditableText.h"

#include "TableLibrary/DataTable/DataManager/MCStringTableDataRecordMgr.h"
#include "TableLibrary/Manager/CSTableMgr.h"

TSharedRef<SWidget> UCSEditableText::RebuildWidget()
{

	if(g_TableMgrValid)
		this->SetHintText(ChangeText(g_TableMgr->GeteLocalType(),this->GetHintText()));
	return Super::RebuildWidget();
		
}

FText UCSEditableText::ChangeText(nLocalType::en _elocalType,FText InText)
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
		for(MCStringTableDetailRecord* pRecord:g_TableMgr->GetarrStringTableRecord())
		{
			if(pRecord->m_strKO == m_strText && m_strText != "")
			{
				m_strTid = pRecord->m_strTid;
				g_TableMgr->LocalChange.AddUObject(this,&UCSEditableText::ChangeLocal);
				if(g_TableMgr->GeteLocalType() != nLocalType::KO)
				{
					m_strText = pRecord->m_strEN;
					return FText::FromString(m_strText);
				}
				break;
			}
		}
	}
	
	return FText::FromString(m_strText);
}

void UCSEditableText::ChangeLocal(nLocalType::en _elocalType)
{
	SetHintText(ChangeText(_elocalType,GetHintText()));
}

FText UCSEditableText::RefreshTid()
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
