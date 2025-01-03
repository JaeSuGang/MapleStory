#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "RenderSystem/RenderSubsystem.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/TimeSubsystem.h"
#include "World/World.h"
#include "Level/Level.h"

UEngine::UEngine()
{
	bIsLoop = true;

	GEngine = this;

	if (S_OK != CoInitializeEx(nullptr, COINIT_MULTITHREADED))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	WindowSubsystem = CreateSubsystem<UWindowSubsystem>();

	RenderSubsystem = CreateSubsystem<URenderSubsystem>();

	ResourceSubsystem = CreateSubsystem<UResourceSubsystem>();

	TimeSubsystem = CreateSubsystem<UTimeSubsystem>();

	TimeSubsystem->LateInit();

	WindowSubsystem->LateInit();

	RenderSubsystem->LateInit();

	ResourceSubsystem->LateInit();

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

	TimeSubsystem->SetLastTimePointTime();
	TimeSubsystem->SetDeltaTime(TimeSubsystem->CalculateDeltaTime());
	float fDeltaTime = TimeSubsystem->GetDeltaTime();

	WindowSubsystem->Tick(fDeltaTime);

	if (!bIsLoop)
		return;

	RenderSubsystem->Tick(fDeltaTime);

#ifdef _DEBUG

	if (DebugSubsystem)
		DebugSubsystem->Tick(fDeltaTime);

#endif // _DEBUG

	this->ExecuteActorDestroy();
}

void UEngine::Terminate()
{
	bIsLoop = false;
}

ENGINE_API void UEngine::DebugLog(string Text, int WarningLevel)
{
	DebugSubsystem->Log(Text, WarningLevel);
}

UWorld* UEngine::GetWorld() const
{
	return ActiveWorld.get();
}

void UEngine::ExecuteActorDestroy()
{
	ActiveWorld->ExecuteActorDestroy();
}

UEngine* GEngine = nullptr;
