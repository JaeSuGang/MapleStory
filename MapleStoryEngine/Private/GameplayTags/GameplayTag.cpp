#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"

bool FGameplayTag::operator==(const FGameplayTag& _Other) const
{
	return this->ID == _Other.ID;
}
