
#include "ActorLibrary/Actor/Builder/CSActorBuilder.h"

template <class TShellType>
TShellType* CSActorShell::ConvertShell()
{
	TShellType* _pDerivedShell = ::Cast<TShellType>(&m_UEActor);
	return _pDerivedShell;
}

template <typename TCompType>
TCompType* CSActorShell::GetComponent(EShellComponentType _eCompType)
{
	return static_cast<TCompType*>(m_ShellComponents.FindRef(_eCompType).Get());
}

template <typename TCompType>
TCompType* CSActorShell::GetUnrealComponent()
{
	return ::Cast<TCompType>(m_UEActor.GetComponentByClass(TCompType::StaticClass()));
}

template <typename TCompType>
TArray<TCompType*> CSActorShell::GetUnrealComponents(bool _bIncludeFromChildActors /*= false*/)
{
	TArray<TCompType*> _OutComponents;
	m_UEActor.GetComponents(_OutComponents, _bIncludeFromChildActors);

	return _OutComponents;
}

template <typename TCompType>
TArray<TCompType*> CSActorShell::GetUnrealComponentsByTag(const FName& _strTag)
{
	TArray<UActorComponent*> _tagActorComponents = m_UEActor.GetComponentsByTag(TCompType::StaticClass(), _strTag);

	TArray<TCompType*> _OutComponents;
	for (auto iter : _tagActorComponents)
	{
		if (TCompType* _pComp = ::Cast<TCompType>(iter))
			_OutComponents.Add(iter);
	}

	return _OutComponents;
}

template <typename TCompType>
TCompType* CSActorShell::GetUnrealComponentsByTagUnique(const FName& _strTag)
{
	TArray<UActorComponent*> _OutComponents = m_UEActor.GetComponentsByTag(TCompType::StaticClass(), _strTag);

	for (auto iter : _OutComponents)
	{
		if (TCompType* _pComp = ::Cast<TCompType>(iter))
			return _pComp;
	}

	return nullptr;
}

template <typename TCompType>
TCompType* CSActorShell::AppendUnrealComponent(const FName& _strComponentName, const FName& _strTag /*= NAME_None*/)
{
	TCompType* _pNewComponent = NewObject<TCompType>(&m_UEActor, TCompType::StaticClass(), _strComponentName);
	if(_pNewComponent)
	{
		_pNewComponent->RegisterComponent();

		if (_strTag.IsNone() == false)
			_pNewComponent->ComponentTags.Add(_strTag);

		m_UEActor.AddInstanceComponent(_pNewComponent);
	}
	return _pNewComponent;
}
