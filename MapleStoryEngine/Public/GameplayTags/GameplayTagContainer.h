#pragma once
#include "EnginePch.h"

struct FGameplayTag;

struct FGameplayTagContainer
{
public:
	ENGINE_API FGameplayTagContainer();

	ENGINE_API void AddTag(FGameplayTag& );

	ENGINE_API bool HasTag(FGameplayTag& );

	ENGINE_API bool HasTagExact(FGameplayTag& );

protected:
	
	 vector<FGameplayTag> Tags;
};

