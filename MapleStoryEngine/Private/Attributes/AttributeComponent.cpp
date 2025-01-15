#include "EnginePch.h"
#include "Attributes/AttributeComponent.h"
#include "Engine/Engine.h"
#include "GameplayTags/GameplayTagsManager.h"

void UAttributeComponent::BeginPlay()
{

}

void UAttributeComponent::TickComponent(float fDeltaTime)
{

}

void UAttributeComponent::SetAttributeValue(FGameplayTag _Tag, float _Value)
{
	Attributes.find(_Tag.ID)->second = _Value;
}

float UAttributeComponent::GetAttributeValue(FGameplayTag _Tag)
{
	return Attributes.find(_Tag.ID)->second;
}

bool UAttributeComponent::HasAttributeExact(FGameplayTag _Tag)
{
	auto FindIter = Attributes.find(_Tag.ID);

	return FindIter != Attributes.end();
}

void UAttributeComponent::AddAttribute(FGameplayTag _Tag)
{
	auto FindIter = Attributes.find(_Tag.ID);

	if (FindIter != Attributes.end())
		return;

	Attributes.insert(std::make_pair(_Tag.ID, 0.0f));
}

void UAttributeComponent::AddAttribute(string _TagName)
{
	FGameplayTag Tag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagExact(_TagName);

	this->AddAttribute(Tag);
}

void UAttributeComponent::RemoveAttribute(FGameplayTag _Tag)
{
	auto FindIter = Attributes.find(_Tag.ID);

	if (FindIter == Attributes.end())
		return;

	Attributes.erase(FindIter);
}

void UAttributeComponent::RemoveAttribute(string _TagName)
{
	FGameplayTag Tag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagExact(_TagName);

	this->RemoveAttribute(Tag);
}
