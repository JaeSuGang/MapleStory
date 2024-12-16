#pragma once
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"
#include "GameplayTags/GameplayTag.h"

class AActor;

class UGameplayTagsManager : public UGameInstanceSubsystem
{
	/* Tag ��Ÿ�� ���� ���� */
public:
	UGameplayTagsManager();

	ENGINE_API void RegisterTag(string TagName);

public:
	/* Registered by ID Order */
	/* RegisteredTags[n]�� ���� ID Index ���� */
	/* [TagID] = Tag��ü �ڽ� */
	vector<FGameplayTag> RegisteredTags;

	/* [TagID] = �θ� �±� ID�� */
	vector<vector<int>> ParentsTags;

	/* string �˻��� ���� TagID�� ������ */
	unordered_map<string, int> StringMappedTags;
};

