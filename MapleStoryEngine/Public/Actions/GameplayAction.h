#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameplayTags/GameplayTag.h"
#include "Engine/TimeSubsystem.h"

class AActor;
class UGameplayTagsManager;
class UActionComponent;
class UWorld;

class UGameplayAction : public UObject
{
	friend class UActionComponent;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API UGameplayAction();

	ENGINE_API virtual void StartAction(AActor* Instigator);

	ENGINE_API virtual void StartAction(AActor* Instigator, void* _ParameterStruct);

	ENGINE_API virtual void StartAction(void* _ParameterStruct);

	ENGINE_API virtual void Tick(float fDeltaTime);

public:
	ENGINE_API UWorld* GetWorld() const;

	ENGINE_API FGameplayTag& GetTag();


protected:
	UActionComponent* ActionComponent;

	UTimeSubsystem* Timesubsystem;

	UGameplayTagsManager* GameplayTagsManager;

	FGameplayTag Tag;

	bool IsTickEnabled;
};

