#include "EnginePch.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "GameplayTags/GameplayTag.h"

UGameplayTagsManager::UGameplayTagsManager()
{
	RegisteredTags.reserve(REGISTERED_TAGS_RESERVE_COUNT);
}

ENGINE_API void UGameplayTagsManager::RegisterTag(string TagName)
{
	FGameplayTag NewTag{};

	NewTag.TagName = TagName;


}
