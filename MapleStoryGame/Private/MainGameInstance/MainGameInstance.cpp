#include "GamePch.h"
#include "MainGameInstance/MainGameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"

UMainGameInstance::UMainGameInstance()
{
	GameplayTagManager = CreateSubsystem<UGameplayTagsManager>();

	GameplayTagManager->RegisterTag("Status.Debuff.Stunned");

	GameplayTagManager->RegisterTag("Status.Debuff.Poisoned");

	GameplayTagManager->RegisterTag("Status.Debuff.Bleeding");

	GameplayTagManager->RegisterTag("Status.Buff.AttackIncreased");

	GameplayTagManager->RegisterTag("Action.TakeDamage");
}

