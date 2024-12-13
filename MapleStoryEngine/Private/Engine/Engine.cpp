#include "pch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"

UEngine::UEngine()
{
	bIsLoop = true;

	Subsystems.reserve(100);

	WindowSubsystem = CreateDefaultSubobject<UWindowSubsystem>();
}

UEngine::~UEngine()
{
	GEngine = nullptr;
}

shared_ptr<UEngine> UEngine::GetShared()
{
	if (GEngine == nullptr)
	{
		GEngine = new UEngine{};
	}

	shared_ptr<UEngine> Engine{ GEngine };
	return Engine;
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
