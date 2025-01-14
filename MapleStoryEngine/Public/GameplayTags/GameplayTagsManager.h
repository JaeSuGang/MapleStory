#pragma once
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"
#include "GameplayTags/GameplayTag.h"

class AActor;

class UGameplayTagsManager : public UGameInstanceSubsystem
{
	/* Tag ��Ÿ�� ���� ���� */

public:
	ENGINE_API UGameplayTagsManager();

	ENGINE_API void RegisterTag(string TagName);

	ENGINE_API FGameplayTag FindRegisteredTagExact(string TagName);

private:
	void ExtractParentsFromString(string StringToParse, vector<string>& Parents);

	int FindRegisteredTagIDExact(string TagName);

private:
	/* Registered by ID Order */
	/* RegisteredTags[n]�� ���� ID Index ���� */
	/* [TagID] = Tag��ü �ڽ� */
	vector<FGameplayTag> RegisteredTags;

	/* [TagID] = �θ� �±� ID�� */
	vector<vector<int>> ParentIDs;

	/* string �˻��� ���� TagID�� ������ */
	unordered_map<string, int> StringMappedIDs;
};

