#pragma once
#include "EnginePch.h"

struct FGameplayTag
{
public:
	ENGINE_API bool operator==(const FGameplayTag& _Other) const;

public:
	string TagName;
	int ID;
};

