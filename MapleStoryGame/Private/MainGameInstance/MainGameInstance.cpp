#include "GamePch.h"
#include "Engine/Engine.h"
#include "Levels/TestLevel.h"
#include "Levels/LachelnTowerTopLevel.h"
#include "Levels/LachelnDreamForest.h"
#include "Levels/TestLevel2.h"
#include "MainGameInstance/MainGameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "GameInstance/GameplaySubsystem.h"
#include "DebugSubsystem/MapleStoryDebugSubsystem.h"

UMainGameInstance::UMainGameInstance()
{
	this->InitTags();
}

void UMainGameInstance::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine->IsDebug)
	{
		GEngine->DebugSubsystem = GEngine->CreateSubsystem<UMapleStoryDebugSubsystem>();

		GEngine->DebugSubsystem->LateInit();
	}

	GameplaySubsystem->OpenLevel<ULachelnDreamForest>();
}

void UMainGameInstance::InitTags()
{
	GameplayTagsManager->RegisterTag("Action.SongOfHeaven");

	GameplayTagsManager->RegisterTag("Action.MistralSpring");

	GameplayTagsManager->RegisterTag("Action.HowlingGale");

	GameplayTagsManager->RegisterTag("Action.IdleWhim");

	GameplayTagsManager->RegisterTag("Action.FairyTurn");

	GameplayTagsManager->RegisterTag("Action.GustShift");

	GameplayTagsManager->RegisterTag("Action.MoveLeft");

	GameplayTagsManager->RegisterTag("Action.MoveRight");

	GameplayTagsManager->RegisterTag("Action.Jump");

	GameplayTagsManager->RegisterTag("Action.Prone");

	GameplayTagsManager->RegisterTag("Action.TakeDamage");

	GameplayTagsManager->RegisterTag("Status.Hitable");

	GameplayTagsManager->RegisterTag("Status.Stunned");

	GameplayTagsManager->RegisterTag("Status.Falling");

	GameplayTagsManager->RegisterTag("Status.Proning");

	GameplayTagsManager->RegisterTag("Status.Walking");

	GameplayTagsManager->RegisterTag("Status.Attacking.ShootMoving");

	GameplayTagsManager->RegisterTag("Status.Attacking.SwingT1");

	GameplayTagsManager->RegisterTag("Status.Attacking.Shoot1");

	GameplayTagsManager->RegisterTag("Status.CanDoubleJump");

	GameplayTagsManager->RegisterTag("Value.MaxHp");

	GameplayTagsManager->RegisterTag("Value.Hp");

	GameplayTagsManager->RegisterTag("Value.Damage");

	GameplayTagsManager->RegisterTag("ActorType.Character");

	GameplayTagsManager->RegisterTag("ActorType.Monster");

	GameplayTagsManager->RegisterTag("ActorType.Boss");
}

