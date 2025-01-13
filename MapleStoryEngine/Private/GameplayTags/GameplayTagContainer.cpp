#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "GameplayTags/GameplayTagContainer.h"
#include "Engine/Engine.h"

FGameplayTagContainer::FGameplayTagContainer()
{
    Tags.reserve(TAG_CONTAINER_RESERVE_COUNT);

    TagManager = GEngine->GetGameInstance()->GameplayTagsManager;
}

bool FGameplayTagContainer::HasTagExact(string _Name) const
{
    FGameplayTag Tag = TagManager->FindRegisteredTagExact(_Name);

    return this->HasTagExact(Tag);
}

bool FGameplayTagContainer::HasTagExact(FGameplayTag& _Tag) const
{
    for (const FGameplayTag& LoopingTag : Tags)
    {
        if (_Tag == LoopingTag)
        {
            return true;
        }
    }

    return false;
}

