// Fill out your copyright notice in the Description page of Project Settings.

template<typename HubType, typename ManagerType, typename HubMgrID>
void CSManagerHub<HubType, ManagerType, HubMgrID>::Release()
{
	for (int i = 0; i < ManagerHub::EManageState::Max; ++i)
	{
		this->ReleaseManager(static_cast<ManagerHub::EManageState::en>(i));
		m_ManagerContainer[i].Empty();
	}
	m_CurrentManageState = ManagerHub::EManageState::Max;
}

template<typename HubType, typename ManagerType, typename HubMgrID>
void CSManagerHub<HubType, ManagerType, HubMgrID>::Init(const ManagerHub::EManageState::en& _eState, const HubMgrID& _eMgrID, ManagerType* _pManager)
{
	if (_eState != ManagerHub::EManageState::Max)
	{
		m_ManagerContainer[_eState].Add(_eMgrID, _pManager);
	}
}

template<typename HubType, typename ManagerType, typename HubMgrID>
void CSManagerHub<HubType, ManagerType, HubMgrID>::LoadManager(const ManagerHub::EManageState::en& _eState)
{
	if (_eState == ManagerHub::EManageState::eGlobalInit)
	{
		for (auto& iter : m_ManagerContainer[ManagerHub::EManageState::eGlobalInit])
		{
			if (iter.Value)
			    iter.Value->Load();
		}
		return;
	}

	if (_eState != ManagerHub::EManageState::Max)
	{
		this->ReleaseManager(m_CurrentManageState);

		for (auto& iter : m_ManagerContainer[_eState])
		{
			if (iter.Value)
			    iter.Value->Load();
		}

		m_CurrentManageState = _eState;
	}
}

template<typename HubType, typename ManagerType, typename HubMgrID>
void CSManagerHub<HubType, ManagerType, HubMgrID>::ReleaseManager(const ManagerHub::EManageState::en& _eState)
{
	if (_eState != ManagerHub::EManageState::Max)
	{
		for (auto& iter : m_ManagerContainer[_eState])
		{
			if (iter.Value)
			    iter.Value->Release();
		}
	}
}