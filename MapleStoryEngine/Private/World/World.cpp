#include "EnginePch.h"
#include "Level/Level.h"
#include "World/World.h"
#include "World/PhysicsSubsystem.h"
#include "RenderSystem/RenderSubsystem.h"

UWorld::UWorld()
{
	PhysicsSubsystem = CreateDefaultSubobject<UPhysicsSubsystem>();
}

UWorld::~UWorld()
{
	GEngine->RenderSubsystem->ReleaseTextures();
}

void UWorld::LateInit()
{
	PhysicsSubsystem->LateInit();
}

ENGINE_API void UWorld::DestroyActor(AActor* Actor)
{
	PersistentLevel->ActorsToDestroy.push_back(Actor);
}

vector<shared_ptr<AActor>>& UWorld::GetActors()
{
	return PersistentLevel->Actors;
}

void UWorld::ExecuteActorTick(float fDeltaTime)
{
	for (shared_ptr<AActor>& LoopActor : PersistentLevel->Actors)
	{
		if (LoopActor->GetIsBeginPlayed())
		{
			LoopActor->Tick(fDeltaTime);
		}
	}
}

void UWorld::ExecuteActorBeginPlay()
{
	for (AActor* LoopActor : PersistentLevel->ActorsToBeginPlay)
	{
		LoopActor->BeginPlay();
	}

	PersistentLevel->ActorsToBeginPlay.clear();
}

void UWorld::ExecuteActorDestroy()
{
	vector<AActor*>& ActorsToDestroy = PersistentLevel->ActorsToDestroy;

	auto RemoveIter = std::remove_if(
		PersistentLevel->Actors.begin(),
		PersistentLevel->Actors.end(),
		[&](shared_ptr<AActor> ActorInContainer)
		{
			for (AActor* pActorToDestroy : ActorsToDestroy)
			{
				if (ActorInContainer.get() == pActorToDestroy)
				{
					return true;
				}
			}

			return false;
		});

	PersistentLevel->Actors.erase(RemoveIter, PersistentLevel->Actors.end());

	ActorsToDestroy.clear();
}
