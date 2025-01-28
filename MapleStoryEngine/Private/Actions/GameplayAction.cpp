#include "EnginePch.h"
#include "Actions/GameplayAction.h"
#include "Engine/Engine.h"
#include "GameInstance/GameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"

UGameplayAction::UGameplayAction()
{
	IsTickEnabled = false;

	GameplayTagsManager = GEngine->GetGameInstance()->GameplayTagsManager;

	Timesubsystem = GEngine->TimeSubsystem;
}

UWorld* UGameplayAction::GetWorld() const
{
	return GEngine->GetWorld();
}

FGameplayTag& UGameplayAction::GetTag()
{
	return Tag;
}

void UGameplayAction::StartAction(AActor* Instigator)
{

}

void UGameplayAction::StartAction(AActor* Instigator, void* _ParameterStruct)
{

}

void UGameplayAction::StartAction(void* _ParameterStruct)
{

}

void UGameplayAction::Tick(float fDeltaTime)
{

}

