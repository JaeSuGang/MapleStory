#include "EnginePch.h"
#include "Level/Level.h"

ULevel::ULevel()
{
	Actors.reserve(3000);
	ActorsToDestroy.reserve(100);
	ActorsToBeginPlay.reserve(100);
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
