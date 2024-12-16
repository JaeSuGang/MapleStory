#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"

class UEngineSubsystem;
class UWindowSubsystem;
class UDebugSubsystem;
class UWorld;
class UGameInstance;

class UEngine : public UObject
{
private:
	UEngine();

public:
	~UEngine();

	ENGINE_API static shared_ptr<UEngine> GetShared();

	ENGINE_API void RunForever();

	ENGINE_API void Terminate();

	void AssignDeltaTime();

	void CalculateDeltaTime();

	void Tick();

	template<typename T>
	void SetGameInstance()
	{
		ActiveGameInstance = std::make_shared<T>();
	}

	template<typename T>
	T* CreateDefaultSubobject()
	{
		T* NewSubsystem = new T{};
		shared_ptr<UEngineSubsystem> NewSharedSubsystem{ NewSubsystem };
		std::pair<string, shared_ptr<UEngineSubsystem>> NewPair{ typeid(T).name(), NewSharedSubsystem };
		Subsystems.insert(NewPair);
		return NewSubsystem;
	}

private:
	UWindowSubsystem* WindowSubsystem;

	UDebugSubsystem* DebugSubsystem;

	shared_ptr<UGameInstance> ActiveGameInstance;

	shared_ptr<UWorld> ActiveWorld;

	unordered_map<string, shared_ptr<UEngineSubsystem>> Subsystems;

	bool bIsLoop;
};

ENGINE_API extern UEngine* GEngine;
