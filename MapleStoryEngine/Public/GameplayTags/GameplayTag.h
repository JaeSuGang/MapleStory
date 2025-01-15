#pragma once
#include "EnginePch.h"

struct FGameplayTag
{
public:
	ENGINE_API FGameplayTag() = default;

	ENGINE_API FGameplayTag(string _TagName);

	ENGINE_API bool operator==(const FGameplayTag& _Other) const;

public:
	string TagName;
	int ID;
};

