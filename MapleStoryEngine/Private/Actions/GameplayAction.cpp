#include "EnginePch.h"
#include "Actions/GameplayAction.h"
#include "Engine/Engine.h"
#include "GameInstance/GameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"

UGameplayAction::UGameplayAction()
{
	GameplayTagsManager = GEngine->GetGameInstance()->GameplayTagsManager;

	Timesubsystem = GEngine->TimeSubsystem;
}

FGameplayTag& UGameplayAction::GetTag()
{
	return Tag;
}

void UGameplayAction::StartAction(AActor* Instigator)
{

}

