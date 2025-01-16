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
	GameplayTagsManager->RegisterTag("Action.FairyTurn");

	GameplayTagsManager->RegisterTag("Action.GustShift");

	GameplayTagsManager->RegisterTag("Action.MoveLeft");

	GameplayTagsManager->RegisterTag("Action.MoveRight");

	GameplayTagsManager->RegisterTag("Action.Jump");

	GameplayTagsManager->RegisterTag("Status.Falling");

	GameplayTagsManager->RegisterTag("Status.Walking");

	GameplayTagsManager->RegisterTag("Status.Attacking.SwingT1");

	GameplayTagsManager->RegisterTag("Status.CanDoubleJump");

}

void UMainGameInstance::BeginPlay()
{
	Super::BeginPlay();

	GEngine->DebugSubsystem = GEngine->CreateSubsystem<UMapleStoryDebugSubsystem>();

	GEngine->DebugSubsystem->LateInit();

	GameplaySubsystem->OpenLevel<UTestLevel>();
}

