#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/DebugSubsystem.h"

UEngine::UEngine()
{
	bIsLoop = true;

	Subsystems.reserve(100);

	WindowSubsystem = CreateDefaultSubobject<UWindowSubsystem>();

	DebugSubsystem = CreateDefaultSubobject<UDebugSubsystem>();
}

UEngine::~UEngine()
{
	GEngine = nullptr;
}

ENGINE_API shared_ptr<UEngine> UEngine::Instantiate()
{
	shared_ptr<UEngine> SharedEngine;

	if (GEngine == nullptr)
	{
		SharedEngine = std::make_shared<UEngine>();
		GEngine = SharedEngine.get();
	}

	return SharedEngine;
}

void UEngine::RunForever()
{
	while (bIsLoop)
	{
		Tick();
	}
}

void UEngine::Tick()
{
	for (auto& EngineSubsystemPair : Subsystems)
	{
		if (UEngineSubsystem* EngineSubsystem = EngineSubsystemPair.second.get())
		{
			EngineSubsystem->Tick(0.0f);
		}
	}
}

void UEngine::Terminate()
{
	bIsLoop = false;
}

UEngine* GEngine = nullptr;
