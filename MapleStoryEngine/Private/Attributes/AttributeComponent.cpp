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
	return Attributes.SetTagValue(_Tag, _Value);
}

void UAttributeComponent::SetAttributeValue(string _TagName, float _Value)
{
	return Attributes.SetTagValue(_TagName, _Value);
}

float UAttributeComponent::GetAttributeValue(string _TagName)
{
	return Attributes.GetTagValue(_TagName);
}

float UAttributeComponent::GetAttributeValue(FGameplayTag _Tag)
{
	return Attributes.GetTagValue(_Tag);
}

bool UAttributeComponent::ContainsAttribute(string _TagName)
{
	return Attributes.ContainsTag(_TagName);
}

bool UAttributeComponent::ContainsAttribute(FGameplayTag _Tag)
{
	return Attributes.ContainsTag(_Tag);
}

bool UAttributeComponent::HasAttributeExact(string _TagName)
{
	return Attributes.HasTagExact(_TagName);
}

bool UAttributeComponent::HasAttributeExact(FGameplayTag _Tag)
{
	return Attributes.HasTagExact(_Tag);
}

void UAttributeComponent::AddAttribute(FGameplayTag _Tag)
{
	Attributes.AddTag(_Tag);
}

void UAttributeComponent::AddAttribute(string _TagName)
{
	Attributes.AddTag(_TagName);
}

void UAttributeComponent::AddAttribute(string _TagName, float _val)
{
	this->AddAttribute(_TagName);

	this->SetAttributeValue(_TagName, _val);
}

void UAttributeComponent::RemoveAttribute(FGameplayTag _Tag)
{
	Attributes.RemoveTag(_Tag);
}

void UAttributeComponent::RemoveAttribute(string _TagName)
{
	Attributes.RemoveTag(_TagName);
}
