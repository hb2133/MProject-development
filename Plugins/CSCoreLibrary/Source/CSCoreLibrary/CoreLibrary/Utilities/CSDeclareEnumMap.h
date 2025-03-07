#pragma once

#include "CoreMinimal.h"

#define DeclareEnumMap() \
\
static inline void BuildMap(); \
static inline en GetEnum(FString fStr, bool bLower); \
static inline FString GetFStr(en e, bool bLower); \
static inline FName GetFName(en e, bool bLower); \
static inline bool IsValid(en e); \
\
typedef TMap<FString, en> _Map; \
\
template<class T> \
class EnumStrMap \
{ \
private: \
	friend class InsertMap; \
\
public:\
	EnumStrMap() {} \
\
public:\
	static EnumStrMap& GetInstance() \
	{ \
		static EnumStrMap StrMapInst; \
		if(StrMapInst.bInitialized == false) \
		{ \
			StrMapInst.bInitialized = true; \
			BuildMap(); \
		} \
		return StrMapInst; \
	} \
public: \
	friend inline en GetEnum(FString fStr, bool bLower); \
	friend inline FString GetFStr(en e, bool bLower); \
\
	static _Map& GetTable() { return GetInstance().TableMap; } \
	static _Map& GetTableLower() { return GetInstance().TableMapLower; } \
\
	_Map TableMap; \
	_Map TableMapLower; \
\
	bool bInitialized = false; \
}; \
\
class InsertMap \
{ \
private: \
	friend inline void BuildMap();	\
	\
private: \
	inline InsertMap(en e, const char* str) \
	{ \
		FString fStr = str; \
		FString fStrLower = fStr.ToLower(); \
		EnumStrMap<en>::GetTable().Add(fStr, e); \
		EnumStrMap<en>::GetTableLower().Add(fStrLower, e); \
	} \
}; \
\
static inline en GetEnum(FString fStr, bool bLower) \
{ \
	_Map& _TableMap = bLower ? EnumStrMap<en>::GetTableLower() : EnumStrMap<en>::GetTable(); \
	FString _keyStr = bLower ? fStr.ToLower() : fStr; \
	if(_TableMap.Contains(fStr)) \
		return _TableMap.FindRef(fStr); \
	return en::Max; \
} \
\
static inline FString GetFStr(en e, bool bLower) \
{\
	_Map& _TableMap = bLower ? EnumStrMap<en>::GetTableLower() : EnumStrMap<en>::GetTable(); \
	for(auto iter : _TableMap) \
	{ \
		if(iter.Value == e) \
			return iter.Key; \
	} \
	return FString(""); \
}\
\
static inline FName GetFName(en e, bool bLower) \
{\
	return *GetFStr(e, bLower); \
}\
\
static inline bool IsValid(en e) \
{\
	return (0 <= e) && (e < en::Max); \
}

#define CSEnumStruct namespace
#define CSEnumDefault enum en : int

#define CSEnumMapRegist \
        DeclareEnumMap() \
        static inline void BuildMap()
