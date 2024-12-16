#pragma once
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"
#include "GameplayTags/GameplayTag.h"

class AActor;

class UGameplayTagsManager : public UGameInstanceSubsystem
{
	/* Tag 런타임 삭제 금지 */
public:
	UGameplayTagsManager();

	ENGINE_API void RegisterTag(string TagName);

public:
	/* Registered by ID Order */
	/* RegisteredTags[n]을 통한 ID Index 접근 */
	/* [TagID] = Tag객체 자신 */
	vector<FGameplayTag> RegisteredTags;

	/* [TagID] = 부모 태그 ID들 */
	vector<vector<int>> ParentsTags;

	/* string 검색을 통해 TagID를 가져옴 */
	unordered_map<string, int> StringMappedTags;
};

