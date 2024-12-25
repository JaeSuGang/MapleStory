#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "World/World.h"
#include "GameInstance/GameInstance.h"

class UEngineSubsystem;
class UWindowSubsystem;
class URenderSubsystem;
class UDebugSubsystem;
class UWorld;

class UEngine : public UObject
{
public:
	UEngine();
	~UEngine();

	ENGINE_API static shared_ptr<UEngine> Instantiate();

	ENGINE_API void RunForever();

	ENGINE_API void Terminate();

	UWorld* GetWorld() const;

	void Tick();

	template<typename T>
	T* OpenLevel()
	{
		static_assert(std::is_base_of<ULevel, T>::value);

		ActiveWorld = std::make_shared<UWorld>();

		ActiveWorld->PersistentLevel = std::static_pointer_cast<ULevel>(std::make_shared<T>());

		return std::static_pointer_cast<T>(ActiveWorld->PersistentLevel).get();
	}

	template<typename T>
	void SetGameInstance()
	{
		ActiveGameInstance = std::static_pointer_cast<UGameInstance>(std::make_shared<T>());

		ActiveGameInstance->BeginPlay();
	}

	template<typename T>
	T* GetSubsystem()
	{
		auto FindIter = Subsystems.find(typeid(T).name());

		if (FindIter == Subsystems.end())
		{
			CRITICAL_ERROR(INVALID_COMPONENT_ERROR_TEXT);
		}

		return static_cast<T*>(FindIter->second().get());
	}

	template<typename T>
	T* CreateDefaultSubobject()
	{
		T* NewSubsystem = new T{};
		NewSubsystem->SetEngine(this);
		shared_ptr<UEngineSubsystem> NewSharedSubsystem{ NewSubsystem };
		std::pair<string, shared_ptr<UEngineSubsystem>> NewPair{ typeid(T).name(), NewSharedSubsystem };
		Subsystems.insert(NewPair);
		return NewSubsystem;
	}

public:
	URenderSubsystem* RenderSubsystem;

	UWindowSubsystem* WindowSubsystem;

	UDebugSubsystem* DebugSubsystem;

private:

	shared_ptr<UGameInstance> ActiveGameInstance;

	shared_ptr<UWorld> ActiveWorld;

	unordered_map<string, shared_ptr<UEngineSubsystem>> Subsystems;

	bool bIsLoop;
};

ENGINE_API extern UEngine* GEngine;
