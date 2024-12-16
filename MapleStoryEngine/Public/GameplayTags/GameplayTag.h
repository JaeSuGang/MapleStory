#pragma once
#include "EnginePch.h"

struct FGameplayTag
{
public:
	FGameplayTag();
	
public:
	vector<int> ParentIDs;
	string TagName;
	int ID;
};

