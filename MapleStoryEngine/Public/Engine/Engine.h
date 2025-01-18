#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "GameInstance/GameInstance.h"

class UEngineSubsystem;
class UKeyInputSubsystem;
class UResourceSubsystem;
class UWindowSubsystem;
class URenderSubsystem;
class UDebugSubsystem;
class UTimeSubsystem;
class UWorld;

class UEngine : public UObject
{
	friend class UGameplaySubsystem;

public:
	ENGINE_API void LateInit();
	UEngine();

	~UEngine();

public:
	ENGINE_API static shared_ptr<UEngine> Instantiate();


	ENGINE_API void RunForever();

	ENGINE_API void Terminate();

	ENGINE_API void DebugLog(string Text, int WarningLevel);

	ENGINE_API UWorld* GetWorld() const;

	ENGINE_API UGameInstance* GetGameInstance() const;

	void WorldTick(float fDeltaTime);

	void LateTick(float fDeltaTime);

	void ExecuteNewWorldIfExists();

	void ExecuteActorDestroy();

	void ExecuteActorBeginPlay();

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
	UKeyInputSubsystem* KeyInputSubsystem;

	UResourceSubsystem* ResourceSubsystem;

	URenderSubsystem* RenderSubsystem;

	UWindowSubsystem* WindowSubsystem;

	UDebugSubsystem* DebugSubsystem;

	UTimeSubsystem* TimeSubsystem;

	bool IsDebug;

private:
	unordered_map<string, shared_ptr<UEngineSubsystem>> Subsystems;

	shared_ptr<UGameInstance> ActiveGameInstance;

	shared_ptr<UWorld> ActiveWorld;

	vector<shared_ptr<UWorld>> WorldToOpen;

	bool bIsLoop;
};

ENGINE_API extern UEngine* GEngine;
