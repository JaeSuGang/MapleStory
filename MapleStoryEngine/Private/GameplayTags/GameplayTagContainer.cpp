#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"
#include "GameplayTags/GameplayTagContainer.h"

FGameplayTagContainer::FGameplayTagContainer()
{
    Tags.reserve(TAG_CONTAINER_RESERVE_COUNT);
}

