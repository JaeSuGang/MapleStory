#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class ULevel;
class AActor;
class UWorldSubsystem;

class UWorld : public UObject
{
public:
	vector<shared_ptr<AActor>>& GetActorContainer();

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

private:
	shared_ptr<ULevel> PersistentLevel;

	unordered_map<string, shared_ptr<UWorldSubsystem>> Subsystems;
};

