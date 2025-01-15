#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"
#include "Engine/TimeSubsystem.h"

class AActor;
class UGameplayTagsManager;
class UWorld;

class UGameplayAction : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API UGameplayAction();

	ENGINE_API virtual void StartAction(AActor* Instigator) = 0;

public:
	ENGINE_API UWorld* GetWorld() const;

	ENGINE_API FGameplayTag& GetTag();


protected:
	UTimeSubsystem* Timesubsystem;

	UGameplayTagsManager* GameplayTagsManager;

	FGameplayTag Tag;
};

