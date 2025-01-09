#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "World/WorldSubsystem.h"

class ULevel;
class UPhysicsSubsystem;

class UWorld : public UObject
{
	friend class UGameplaySubsystem;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API UWorld();

	ENGINE_API ~UWorld();

	ENGINE_API virtual void LateInit();

public:
	ENGINE_API ULevel* GetLevel() const;

	ENGINE_API void DestroyActor(AActor* Actor);

	ENGINE_API vector<shared_ptr<AActor>>& GetActors();

	void ExecutePhysicsTick(float fDeltaTime);

	void ExecuteWorldSubsystemTick(float fDeltaTime);

	void ExecuteActorTick(float fDeltaTime);

	void ExecuteActorDestroy();

	void ExecuteActorBeginPlay();

	template <typename T>
	T* SpawnActor()
	{
		static_assert(std::is_base_of<AActor, T>::value);

		shared_ptr<AActor> NewActor{ static_cast<AActor*>(new T{}) };

		NewActor->SetWorld(this);

		PersistentLevel->Actors.push_back(NewActor);

		PersistentLevel->ActorsToBeginPlay.push_back(NewActor.get());

		return static_cast<T*>(NewActor.get());
	}

	template <typename T>
	T* CreateDefaultSubobject()
	{
		static_assert(std::is_base_of<UWorldSubsystem, T>::value);

		shared_ptr<UWorldSubsystem> NewSubsystem{ new T{} };
		NewSubsystem->SetWorld(this);
		Subsystems.insert(std::make_pair(typeid(T).name(), NewSubsystem));
		return static_cast<T*>(NewSubsystem.get());
	}

	template <typename T>
	T* GetSubsystem()
	{
		auto FindIter = Subsystems.find(typeid(T).name());

		if (FindIter == Subsystems.end())
			return nullptr;

		return static_cast<T*>(FindIter->second.get());
	}

public:
	UPhysicsSubsystem* PhysicsSubsystem;

private:
	unordered_map<string, shared_ptr<UWorldSubsystem>> Subsystems;

	shared_ptr<ULevel> PersistentLevel;
};

