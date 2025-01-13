#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"

class AActor;
class UGameplayTagsManager;

class UGameplayAction : public UObject
{
public:
	/* �����ڿ� �������̵� */
	ENGINE_API UGameplayAction();

	ENGINE_API virtual void StartAction(AActor* Instigator) = 0;

public:
	ENGINE_API FGameplayTag& GetTag();


protected:
	UGameplayTagsManager* GameplayTagsManager;

	FGameplayTag Tag;
};

