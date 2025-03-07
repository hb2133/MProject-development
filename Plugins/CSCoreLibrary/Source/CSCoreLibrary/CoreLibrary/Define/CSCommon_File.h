#pragma once

#include "CoreMinimal.h"

struct FolderPathNode
{
	FolderPathNode* _pParent = nullptr;
	FName _CurNodeName;
};
typedef TSharedPtr<FolderPathNode> FolderPathNodePtr;