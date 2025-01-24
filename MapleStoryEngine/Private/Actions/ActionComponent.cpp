#include "EnginePch.h"
#include "Actions/ActionComponent.h"
#include "Engine/Engine.h"
#include "GameplayTags/GameplayTag.h"
#include "GameInstance/GameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actions/GameplayAction.h"


bool UActionComponent::HasAction(string _Name)
{
	FGameplayTag ActionTag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagExact(_Name);

	for (shared_ptr<UGameplayAction>& GameplayAction : Actions)
	{
		if (GameplayAction->GetTag() == ActionTag)
		{
			return true;
		}
	}

	return false;
}

void UActionComponent::StartActionByNameWithParameter(AActor* Instigator, string Name, void* pParameter)
{
	FGameplayTag ActionTag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagExact(Name);

	this->StartActionByTag(Instigator, ActionTag, pParameter);
}

void UActionComponent::StartActionByName(AActor* Instigator, string Name)
{
	FGameplayTag ActionTag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagExact(Name);

	this->StartActionByTag(Instigator, ActionTag);
}

void UActionComponent::StartActionByTag(AActor* Instigator, FGameplayTag& ActionTag, void* pParameter)
{
	for (shared_ptr<UGameplayAction>& GameplayAction : Actions)
	{
		if (GameplayAction->GetTag() == ActionTag)
		{
			GameplayAction->StartAction(Instigator, pParameter);
			return;
		}
	}
}

void UActionComponent::StartActionByTag(AActor* Instigator, FGameplayTag& ActionTag)
{
	for (shared_ptr<UGameplayAction>& GameplayAction : Actions)
	{
		if (GameplayAction->GetTag() == ActionTag)
		{
			GameplayAction->StartAction(Instigator);
			return;
		}
	}
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UActionComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);

	for (shared_ptr<UGameplayAction>& Action : Actions)
	{
		if (Action->IsTickEnabled)
			Action->Tick(fDeltaTime);
	}
}
