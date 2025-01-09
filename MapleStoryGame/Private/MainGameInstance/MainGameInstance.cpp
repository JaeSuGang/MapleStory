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
	GameplayTagManager = CreateSubsystem<UGameplayTagsManager>();

	GameplayTagManager->RegisterTag("Status.Debuff.Stunned");

	GameplayTagManager->RegisterTag("Status.Debuff.Poisoned");

	GameplayTagManager->RegisterTag("Status.Debuff.Bleeding");

	GameplayTagManager->RegisterTag("Status.Buff.AttackIncreased");

	GameplayTagManager->RegisterTag("Action.TakeDamage");
}

void UMainGameInstance::BeginPlay()
{
	Super::BeginPlay();

	GEngine->DebugSubsystem = GEngine->CreateSubsystem<UMapleStoryDebugSubsystem>();

	GEngine->DebugSubsystem->LateInit();

	GameplaySubsystem->OpenLevel<UTestLevel>();
}

