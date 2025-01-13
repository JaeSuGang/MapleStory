#include "EnginePch.h"
#include "GameInstance/GameInstance.h"
#include "GameInstance/GameplaySubsystem.h"

UGameInstance::UGameInstance()
{
	Widgets.resize(2);

	GameplaySubsystem = CreateSubsystem<UGameplaySubsystem>();
}

void UGameInstance::BeginPlay()
{

}

vector<vector<shared_ptr<UWidget>>>& UGameInstance::GetWidgets()
{
	return Widgets;
}
