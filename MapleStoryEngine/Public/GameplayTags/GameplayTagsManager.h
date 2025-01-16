#pragma once
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"
#include "GameplayTags/GameplayTag.h"

class AActor;

/* Tag ��Ÿ�� ���� ���� */
class UGameplayTagsManager : public UGameInstanceSubsystem
{
	friend struct FGameplayTagContainer;

public:
	ENGINE_API UGameplayTagsManager();

	ENGINE_API void RegisterTag(string TagName);

	ENGINE_API FGameplayTag FindRegisteredTagExact(string TagName);

	ENGINE_API FGameplayTag FindRegisteredTagByID(int ID);

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

