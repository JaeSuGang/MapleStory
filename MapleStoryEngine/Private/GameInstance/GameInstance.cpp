#include "EnginePch.h"
#include "GameInstance/GameInstance.h"
#include "GameInstance/GameplaySubsystem.h"

UGameInstance::UGameInstance()
{
	GameplaySubsystem = CreateSubsystem<UGameplaySubsystem>();
}

ENGINE_API void UGameInstance::BeginPlay()
{

}