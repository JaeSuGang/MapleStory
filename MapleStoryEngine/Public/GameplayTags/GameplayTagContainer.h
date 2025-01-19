#pragma once
#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"

class UGameplayTagsManager;

struct FGameplayTagContainer
{
public:
	ENGINE_API FGameplayTagContainer();

	ENGINE_API void AddTagValue(string _Name, float fValue);

	ENGINE_API void AddTagValue(FGameplayTag _Tag, float fValue);

	ENGINE_API void SetTagValue(string _Name, float fValue);

	ENGINE_API void SetTagValue(FGameplayTag _Tag, float fValue);

	ENGINE_API float GetTagValue(string _Name);

	ENGINE_API float GetTagValue(FGameplayTag _Tag);

	ENGINE_API void RemoveTag(FGameplayTag _Tag);

	ENGINE_API void RemoveTag(string _Name);

	ENGINE_API void AddTag(FGameplayTag _Tag);

	ENGINE_API void AddTag(string _Name);

	ENGINE_API bool ContainsTag(FGameplayTag _Tag);

	ENGINE_API bool ContainsTag(string _Name);

	ENGINE_API bool HasTagExact(string _Name) const;

	ENGINE_API bool HasTagExact(FGameplayTag _Tag) const;

public:
	UGameplayTagsManager* TagManager;

	unordered_map<int, float> Tags;
};

