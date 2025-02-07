#include "EnginePch.h"
#include "GameInstance/GameInstance.h"
#include "GameInstance/GameplaySubsystem.h"
#include "GameplayTags/GameplayTagsManager.h"

UGameInstance::UGameInstance()
{
	Widgets.resize(10);

	GameplaySubsystem = CreateSubsystem<UGameplaySubsystem>();

	GameplayTagsManager = CreateSubsystem<UGameplayTagsManager>();
}

void UGameInstance::BeginPlay()
{

}

void UGameInstance::ClearWidgets(int _Index)
{
	Widgets[_Index].clear();
}

vector<vector<shared_ptr<UWidget>>>& UGameInstance::GetWidgets()
{
	return Widgets;
}
