#include "GamePch.h"
#include "MainGameInstance/MainGameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"

UMainGameInstance::UMainGameInstance()
{
	GameplayTagManager = CreateSubsystem<UGameplayTagsManager>();
}

