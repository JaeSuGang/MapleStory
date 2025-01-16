#pragma once
#include "EnginePch.h"
#include "ActorComponent/ActorComponent.h"
#include "GameplayTags/GameplayTag.h"
#include "GameplayTags/GameplayTagContainer.h"

class UAttributeComponent : public UActorComponent
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API void BeginPlay() override;

	ENGINE_API void TickComponent(float fDeltaTime) override;

public:

	ENGINE_API void SetAttributeValue(FGameplayTag _Tag, float _Value);

	ENGINE_API void SetAttributeValue(string _TagName, float _Value);

	ENGINE_API float GetAttributeValue(string _TagName);

	ENGINE_API float GetAttributeValue(FGameplayTag _Tag);

	ENGINE_API bool ContainsAttribute(string _TagName);

	ENGINE_API bool ContainsAttribute(FGameplayTag _Tag);

	ENGINE_API bool HasAttributeExact(string _TagName);

	ENGINE_API bool HasAttributeExact(FGameplayTag _Tag);

	ENGINE_API void AddAttribute(FGameplayTag _Tag);

	ENGINE_API void AddAttribute(string _TagName);

	ENGINE_API void RemoveAttribute(FGameplayTag _Tag);

	ENGINE_API void RemoveAttribute(string _TagName);

public:
	FGameplayTagContainer Attributes;
};

