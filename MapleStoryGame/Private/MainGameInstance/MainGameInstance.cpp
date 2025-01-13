#include "GamePch.h"
#include "Engine/Engine.h"
#include "Levels/TestLevel.h"
#include "Levels/TestLevel2.h"
#include "MainGameInstance/MainGameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "GameInstance/GameplaySubsystem.h"
#include "DebugSubsystem/MapleStoryDebugSubsystem.h"

UMainGameInstance::UMainGameInstance()
{
	GameplayTagsManager->RegisterTag("Status.Debuff.Stunned");

	GameplayTagsManager->RegisterTag("Status.Debuff.Poisoned");

	GameplayTagsManager->RegisterTag("Status.Debuff.Bleeding");

	GameplayTagsManager->RegisterTag("Status.Buff.AttackIncreased");

	GameplayTagsManager->RegisterTag("Action.TakeDamage");
}

void UMainGameInstance::BeginPlay()
{
	Super::BeginPlay();

	GEngine->DebugSubsystem = GEngine->CreateSubsystem<UMapleStoryDebugSubsystem>();

	GEngine->DebugSubsystem->LateInit();

	GameplaySubsystem->OpenLevel<UTestLevel>();
}

