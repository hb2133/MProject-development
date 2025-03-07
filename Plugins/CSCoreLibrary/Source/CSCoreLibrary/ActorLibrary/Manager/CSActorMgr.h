// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreLibrary/Manager/CSBaseManager.h"
#include "CoreLibrary/GameGlobal/CSGameGlobal.h"

#include "ActorLibrary/Actor/Builder/CSActorBuilder.h"
#include "ActorLibrary/Actor/Shell/CSActorShell.h"

#include "ActorLibrary/Define/CSActorCommon.h"
#include "CSCoreLibrary/ActorLibrary/Define/CSCommon_Builder.h"

#include "CSActorMgr.generated.h"


UCLASS()
class CSCORELIBRARY_API UCSActorMgr : public UCSBaseManager
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void Release() override;
	void Load() override;
	void Tick(float _dt) override;
	
public:
	template <class TDerivedBuilderType>
	bool ReserveActorBuilder()
	{
		TSharedPtr<TDerivedBuilderType> _pDerivedBuilder = MakeShareable(new TDerivedBuilderType());
		if (TDerivedBuilderType* _pBuilder = _pDerivedBuilder.Get())
		{
			EActorBuilderType _eActorBuilderType = TDerivedBuilderType::GetBuilderType();
			m_pActorBuilder.Add(_eActorBuilderType, _pDerivedBuilder);
			return true;
		}
		return false;
	}
	void AppendShellBuilder(const EActorBuilderType& _eBuilderType, CSActorShell* _pOwnerShell, const FName& _strActorTid = NAME_None);

	template<class TActorType = CSActorShell>
	TActorType* CreateActor(const EActorBuilderType& _eBuilderType, const STableInfo& _stTableInfo, const SCreationInfo& _stCreationInfo, const UNIQUEID& _nMasterID)
	{
		TActorType* _pShell = this->CreateActor<TActorType>(_eBuilderType, _stTableInfo, _stCreationInfo);
		if (_pShell)
		{
			//:: 액터 아이디로 보관 예정 (풀링 만들어야함)
		}
		return _pShell;
	}

	template<class TActorType = CSActorShell>
	TActorType* CreateActor(const EActorBuilderType& _eBuilderType, const STableInfo& _stTableInfo, const SCreationInfo& _stCreationInfo)
	{
		if (TSharedPtr<CSActorBuilder> _pSharedBuilder = m_pActorBuilder.FindRef(_eBuilderType))
		{
			if (CSActorBuilder* _pBuilder = _pSharedBuilder.Get())
			{
				if (CSActorShell* _pShell = _pBuilder->BuildShell(_stTableInfo, _stCreationInfo))
				{
					_pBuilder->BuildShellComponents(_stTableInfo, _stCreationInfo, _pShell);
					_pShell->SetTableInfo(_stTableInfo);
					return _pShell->ConvertShell<TActorType>();
				}
			}
		}
		return nullptr;
	}

	template<class TActorType = CSActorShell>
	TActorType* FindActor(const UNIQUEID& _nMasterID)
	{
		return nullptr;
	}

private:
	TMap<EActorBuilderType, TSharedPtr<CSActorBuilder>> m_pActorBuilder;
};

#define g_ActorMgrValid ( g_GameGlobal->IsValidManager<UCSActorMgr>() )
#define g_ActorMgr ( g_GameGlobal->GetManager<UCSActorMgr>() )




//:: Legacy CreateActor Fuction : 템플릿 타입 기반 방식, 언리얼 레벨에 직접 배치하는 케이스 이슈가 없다면 이 방식도 좋은 방식이라 주석으로 백업해둔다.
// 템플릿 기반을 사용할때의 장점 : 별도의 키값, 원본 객체 보관이 필요없고, 빌더 클래스가 필요한 타입을 클래스 타입으로 자정할 수 있다.
// 템플릿 기반을 사용할때의 단점 : 원본을 Map 등에 보관하여 타입으로 찾아서 쓰는 방식으로는 작업이 불가능
// 
// -> 언리얼 레벨에 직접 배치하는 경우 생성 기반인 빌더 클래스와 별도로 에디터에 시리얼라이즈 해주어야 할 언리얼 클래스가 필요하였다.
// -> 별도 언리얼 클래스를 모든 빌더 갯수만큼 추가로 생성하는것은 비효율적이었고, 액터 매니저가 미리 필요한 빌더 클래스를 생성하여 보관하는 방식으로 변경하였다.
// -> 따라서 생성시 템플릿으로 빌더의 클래스 형을 알려주는 방식이 아니고, 미리 생성된 빌더를 Map 에서 찾기위해 타입 enum 을 넘겨주는 방식으로 변경

//template<class TDerivedBuilderType, class TActorType = CSActorShell>
//TActorType* CreateActor(const CSActorBuilder::STableInfo& _stTableInfo, const CSActorBuilder::SCreationInfo& _stCreationInfo)
//{
//	TSharedPtr<TDerivedBuilderType> _pDerivedBuilder = MakeShareable(new TDerivedBuilderType(_stTableInfo, _stCreationInfo));
//	if (TDerivedBuilderType* _pBuilder = _pDerivedBuilder.Get())
//	{
//		if (CSActorShell* _pShell = _pBuilder->BuildShell(_stTableInfo, _stCreationInfo))
//		{
//			_pBuilder->BuildShellComponents(_stTableInfo, _stCreationInfo, _pShell);
//			_pShell->SetBuilder(_pDerivedBuilder);
//
//			return _pShell->ConvertShell<TActorType>();
//		}
//	}
//	return 