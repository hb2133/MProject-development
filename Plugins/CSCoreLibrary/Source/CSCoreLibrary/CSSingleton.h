// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


//:: 싱글톤 인터페이스 (+ 상위 클래스 다형성을 쓰기 위해 사용, 
//   템플릿 클래스는 포인터로 선언하기 어려우므로 추가로 상위에 클래스를 붙여준다)
class CSSingletonInterface
{
public:
	virtual ~CSSingletonInterface() {}
	virtual void Load() = 0;
	virtual void Release() = 0;
};

template <typename T>
class CSSingleton : public CSSingletonInterface
{
public:
	CSSingleton() {}
	~CSSingleton() { this->Clear(); }
	virtual void Load() {}
	virtual void Release() {}

public:
	static T* GetInstance()
	{
		if (m_pInst == nullptr)
			m_pInst = new T;
		return m_pInst;
	}

	static void Clear()
	{
		if (m_pInst != nullptr)
		{
			T* _pInst = m_pInst;
			m_pInst = nullptr;
			delete _pInst;
		}
	}

private:
	static T* m_pInst;
};

template <typename T>
T* CSSingleton<T>::m_pInst = nullptr;