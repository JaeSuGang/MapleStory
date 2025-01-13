#pragma once
#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"

struct FGameplayTagContainer
{
public:
	ENGINE_API FGameplayTagContainer();

	ENGINE_API void AddTag(FGameplayTag& );

	ENGINE_API bool HasTag(FGameplayTag& );

	ENGINE_API bool HasTagExact(string _Name) const;

	ENGINE_API bool HasTagExact(FGameplayTag& _Tag) const;

protected:
	UGameplayTagsManager* TagManager;

	 vector<FGameplayTag> Tags;
};

