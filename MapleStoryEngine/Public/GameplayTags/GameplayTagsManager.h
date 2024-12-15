#pragma once
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"
#include "GameplayTags/GameplayTag.h"

class AActor;

class UGameplayTagsManager : UGameInstanceSubsystem
{
public:
	ENGINE_API void RegisterTag();

public:
	unordered_map<FGameplayTag, vector<weak_ptr<AActor>>> Tags;
};

