#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"

class UGameInstanceSubsystem;
class UGameplaySubsystem;
class ULevel;

class UGameInstance : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API UGameInstance();

	ENGINE_API virtual void BeginPlay() = 0;

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

public:
	UGameplaySubsystem* GameplaySubsystem;

protected:
	unordered_map<string, shared_ptr<UGameInstanceSubsystem>> Subsystems;
};

