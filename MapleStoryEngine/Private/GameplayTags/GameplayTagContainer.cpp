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

void FGameplayTagContainer::SetTagValue(string _Name, float fValue)
{
    this->SetTagValue(TagManager->FindRegisteredTagExact(_Name), fValue);
}

void FGameplayTagContainer::SetTagValue(FGameplayTag _Tag, float fValue)
{
    auto FindIter = Tags.find(_Tag.ID);

    FindIter->second = fValue;
}

float FGameplayTagContainer::GetTagValue(string _Name)
{
    return this->GetTagValue(TagManager->FindRegisteredTagExact(_Name));
}

float FGameplayTagContainer::GetTagValue(FGameplayTag _Tag)
{
    auto FindIter = Tags.find(_Tag.ID);

    return FindIter->second;
}

void FGameplayTagContainer::RemoveTag(FGameplayTag _Tag)
{
    if (!this->HasTagExact(_Tag))
        return;

    Tags.erase(_Tag.ID);
}

void FGameplayTagContainer::RemoveTag(string _Name)
{
    this->RemoveTag(TagManager->FindRegisteredTagExact(_Name));
}

void FGameplayTagContainer::AddTag(FGameplayTag _Tag)
{
    if (this->HasTagExact(_Tag))
        return;

    Tags.insert(std::make_pair(_Tag.ID, 0.0f));
}

void FGameplayTagContainer::AddTag(string _Name)
{
    this->AddTag(TagManager->FindRegisteredTagExact(_Name));
}

bool FGameplayTagContainer::ContainsTag(FGameplayTag _Tag)
{
    for (auto LoopPair : Tags)
    {
        int LoopTagID = LoopPair.first;

        for (int ParentID : TagManager->ParentIDs[LoopTagID])
        {
            if (ParentID == _Tag.ID)
                return true;
        }
    }

    return false;
}

bool FGameplayTagContainer::ContainsTag(string _Name)
{
    return this->ContainsTag(TagManager->FindRegisteredTagExact(_Name));
}

bool FGameplayTagContainer::HasTagExact(string _Name) const
{
    FGameplayTag Tag = TagManager->FindRegisteredTagExact(_Name);

    return this->HasTagExact(Tag);
}

bool FGameplayTagContainer::HasTagExact(FGameplayTag _Tag) const
{
    for (auto LoopPair : Tags)
    {
        int LoopTagID = LoopPair.first;

        if (LoopTagID == _Tag.ID)
            return true;
    }

    return false;
}

