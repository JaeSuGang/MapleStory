#pragma once
#include <Windows.h>
#include <memory>
#include <string>
#include <unordered_map>
#include "EngineAPI.h"
#include "UObject/Object.h"

using std::shared_ptr;
using std::unordered_map;
using std::string;

class UEngineSubsystem;
class UWindowSubsystem;

class UEngine : public UObject
{
private:
	UEngine();

public:
	~UEngine();

	ENGINE_API static shared_ptr<UEngine> GetShared();

	ENGINE_API void RunForever();

	ENGINE_API void Terminate();

	void Tick();

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
	unordered_map<string, shared_ptr<UEngineSubsystem>> Subsystems;

	UWindowSubsystem* WindowSubsystem;

	bool bIsLoop;
};

ENGINE_API extern UEngine* GEngine;
