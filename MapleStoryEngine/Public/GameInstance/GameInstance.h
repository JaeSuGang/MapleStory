#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"

class UGameInstanceSubsystem;

class UGameInstance : public UObject
{
public:
	template <typename T>
	T* GetSubsystem()
	{
		static_assert(std::is_base_of<UGameInstanceSubsystem, T>::value);

		auto FindIter = Subsystems.find(typeid(T).name());
		if (FindIter == Subsystems.end())
			return nullptr;

		return FindIter->second.get();
	}

	template <typename T>
	T* CreateSubsystem()
	{
		static_assert(std::is_base_of<UGameInstanceSubsystem, T>::value);

		shared_ptr<UGameInstanceSubsystem> NewSubsystem{ (UGameInstanceSubsystem*)new T{} };
		Subsystems.insert(std::pair<string, shared_ptr<UGameInstanceSubsystem>>{typeid(T).name(), NewSubsystem});
		return static_cast<T*>(NewSubsystem.get());
	}

protected:
	unordered_map<string, shared_ptr<UGameInstanceSubsystem>> Subsystems;
};

