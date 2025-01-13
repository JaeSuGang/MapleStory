#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameInstance/GameInstanceSubsystem.h"

class UGameInstanceSubsystem;
class UGameplaySubsystem;
class UGameplayTagsManager;
class UWidget;
class ULevel;

class UGameInstance : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API UGameInstance();

	ENGINE_API virtual void BeginPlay() = 0;

public:
	ENGINE_API vector<vector<shared_ptr<UWidget>>>& GetWidgets();

	template<typename T>
	T* AddWidget()
	{
		static_assert(std::is_base_of<UWidget, T>::value);

		T* RawWidget = new T{};

		shared_ptr<UWidget> NewWidget{ RawWidget };

		Widgets[0].push_back(NewWidget);

		return RawWidget;
	}

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

	UGameplayTagsManager* GameplayTagsManager;

protected:
	unordered_map<string, shared_ptr<UGameInstanceSubsystem>> Subsystems;

	vector<vector<shared_ptr<UWidget>>> Widgets;
};

