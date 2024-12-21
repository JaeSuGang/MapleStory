#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/RenderSubsystem.h"

UEngine::UEngine()
{
	bIsLoop = true;

	if (S_OK != CoInitializeEx(nullptr, COINIT_MULTITHREADED))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	WindowSubsystem = CreateDefaultSubobject<UWindowSubsystem>();

	DebugSubsystem = CreateDefaultSubobject<UDebugSubsystem>();

	RenderSubsystem = CreateDefaultSubobject<URenderSubsystem>();

	RenderSubsystem->LateInit();
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
	float fDeltaTime{};

	WindowSubsystem->Tick(fDeltaTime);

	RenderSubsystem->Tick(fDeltaTime);
}

void UEngine::Terminate()
{
	bIsLoop = false;
}

UEngine* GEngine = nullptr;
