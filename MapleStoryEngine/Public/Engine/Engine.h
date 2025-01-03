#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameInstance/GameInstance.h"

class UEngineSubsystem;
class UResourceSubsystem;
class UWindowSubsystem;
class URenderSubsystem;
class UDebugSubsystem;
class UWorld;

class UEngine : public UObject
{
	friend class UGameplaySubsystem;

public:
	UEngine();

	~UEngine();

public:
	ENGINE_API static shared_ptr<UEngine> Instantiate();

	ENGINE_API void RunForever();

	ENGINE_API void Terminate();

	ENGINE_API void DebugLog(string Text, int WarningLevel);

	ENGINE_API UWorld* GetWorld() const;

	void ExecuteActorDestroy();

	void Tick();

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
	T* CreateSubsystem()
	{
		T* NewSubsystem = new T{};
		NewSubsystem->SetEngine(this);
		shared_ptr<UEngineSubsystem> NewSharedSubsystem{ NewSubsystem };
		std::pair<string, shared_ptr<UEngineSubsystem>> NewPair{ typeid(T).name(), NewSharedSubsystem };
		Subsystems.insert(NewPair);
		return NewSubsystem;
	}

public:
	UResourceSubsystem* ResourceSubsystem;

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
