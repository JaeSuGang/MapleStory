#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Engine/Engine.h"
#include "GameInstance/GameInstance.h"


FGameplayTag::FGameplayTag(string _TagName)
{
	FGameplayTag Tag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagExact(_TagName);

	this->ID = Tag.ID;
	this->TagName = Tag.TagName;
}

bool FGameplayTag::operator==(const FGameplayTag& _Other) const
{
	return this->ID == _Other.ID;
}