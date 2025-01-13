#include "EnginePch.h"
#include "GameInstance/GameInstance.h"
#include "GameInstance/GameplaySubsystem.h"
#include "GameplayTags/GameplayTagsManager.h"

UGameInstance::UGameInstance()
{
	Widgets.resize(2);

	GameplaySubsystem = CreateSubsystem<UGameplaySubsystem>();

	GameplayTagsManager = CreateSubsystem<UGameplayTagsManager>();
}

void UGameInstance::BeginPlay()
{

}

vector<vector<shared_ptr<UWidget>>>& UGameInstance::GetWidgets()
{
	return Widgets;
}
