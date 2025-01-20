#include "EnginePch.h"
#include "Level/Level.h"

ULevel::ULevel()
	:
	Actors{}
{
	Actors.reserve(20000);
	ActorsToDestroy.reserve(1000);
	ActorsToBeginPlay.reserve(1000);
}

void ULevel::BeginPlay()
{

}

void ULevel::Tick(float fDeltaTime)
{

}

UWorld* ULevel::GetWorld() const
{
	return World;
}

void ULevel::SetWorld(UWorld* _World)
{
	World = _World;
}
