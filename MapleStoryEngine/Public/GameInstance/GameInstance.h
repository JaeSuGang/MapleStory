#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"

class UGameInstanceSubsystem;

class UGameInstance : public UObject
{
public:
	template <typename T>
	T* GetSubsystem()
	{
		auto FindIter = Subsystems.find(typeid(T).name);
		if (FindIter == Subsystems.end())
			return nullptr;

		return FindIter->second.get();
	}

	template <typename T>
	T* CreateSubsystem()
	{
		shared_ptr<T> NewSubsystem{ new T{} };
		Subsystems.insert(NewSubsystem);
		return NewSubsystem;
	}

protected:
	unordered_map<string, shared_ptr<UGameInstanceSubsystem>> Subsystems;
};

