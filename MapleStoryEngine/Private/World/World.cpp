#include "EnginePch.h"
#include "Level/Level.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "RenderCore/RenderSubsystem.h"

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

	PersistentLevel->BeginPlay();
}


float UWorld::GetElapsedTime() const
{
	return ElapsedTime;
}

ULevel* UWorld::GetLevel() const
{
	return PersistentLevel.get();
}

void UWorld::DestroyActor(AActor* Actor)
{
	PersistentLevel->ActorsToDestroy.push_back(Actor);
}

vector<shared_ptr<AActor>>& UWorld::GetActors()
{
	return PersistentLevel->Actors;
}

void UWorld::ExecutePhysicsTick(float fDeltaTime)
{
	PhysicsSubsystem->Tick(fDeltaTime);
}

void UWorld::ExecuteWorldSubsystemTick(float fDeltaTime)
{
	for (auto Pair : Subsystems)
	{
		if (Pair.first == typeid(UPhysicsSubsystem).name())
			continue;

		UWorldSubsystem* WorldSubsystem = Pair.second.get();

		WorldSubsystem->Tick(fDeltaTime);
	}
}

void UWorld::ExecuteLevelTick(float fDeltaTime)
{
	if (PersistentLevel.get())
		PersistentLevel->Tick(fDeltaTime);
}

void UWorld::ExecuteActorTick(float fDeltaTime)
{
	for (shared_ptr<AActor>& LoopActor : PersistentLevel->Actors)
	{
		if (LoopActor->GetIsTickEnabled() && LoopActor->GetIsBeginPlayed())
		{
			LoopActor->Tick(fDeltaTime);
		}
	}
}

void UWorld::ExecuteActorLateTick(float fDeltaTime)
{
	for (shared_ptr<AActor>& LoopActor : PersistentLevel->Actors)
	{
		if (LoopActor->GetIsTickEnabled() && LoopActor->GetIsBeginPlayed())
		{
			LoopActor->LateTick(fDeltaTime);
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
