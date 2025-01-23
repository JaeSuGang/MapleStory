#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "RenderCore/RenderSubsystem.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/KeyInputSubsystem.h"
#include "Engine/TimeSubsystem.h"
#include "Engine/RandomManager.h"
#include "World/World.h"
#include "Level/Level.h"

void UEngine::LateInit()
{
	TimeSubsystem->LateInit();

	WindowSubsystem->LateInit();

	RenderSubsystem->LateInit();

	ResourceSubsystem->LateInit();

	RandomManager->LateInit();
}

UEngine::UEngine()
	:
	IsDebug{},
	RenderSubsystem{},
	WindowSubsystem{},
	DebugSubsystem{},
	TimeSubsystem{},
	ResourceSubsystem{},
	KeyInputSubsystem{}
{
#ifdef _DEBUG
	IsDebug = true;
#endif

	bIsLoop = true;

	GEngine = this;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	if (S_OK != CoInitializeEx(nullptr, COINIT_MULTITHREADED))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	WindowSubsystem = CreateSubsystem<UWindowSubsystem>();

	RenderSubsystem = CreateSubsystem<URenderSubsystem>();

	ResourceSubsystem = CreateSubsystem<UResourceSubsystem>();

	TimeSubsystem = CreateSubsystem<UTimeSubsystem>();

	KeyInputSubsystem = CreateSubsystem<UKeyInputSubsystem>();

	RandomManager = CreateSubsystem<URandomManager>();
}

UEngine::~UEngine()
{

}

shared_ptr<UEngine> UEngine::Instantiate()
{
	shared_ptr<UEngine> SharedEngine;

	if (GEngine == nullptr)
	{
		SharedEngine = std::make_shared<UEngine>();
		GEngine = SharedEngine.get();
		GEngine->LateInit();
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
	TimeSubsystem->SetDeltaTime(TimeSubsystem->CalculateDeltaTime());
	TimeSubsystem->SetLastTimePointTime();
	float fDeltaTime = TimeSubsystem->GetDeltaTime();

	WindowSubsystem->Tick(fDeltaTime);

	if (!bIsLoop)
		return;

	this->ExecuteNewWorldIfExists();

	if (ActiveWorld.get() == nullptr)
		return;

	KeyInputSubsystem->Tick(fDeltaTime);

	this->ActiveWorld->ExecutePhysicsTick(fDeltaTime);

	this->WorldTick(fDeltaTime);

	RenderSubsystem->Tick(fDeltaTime);

#ifdef _DEBUG

	if (DebugSubsystem)
		DebugSubsystem->Tick(fDeltaTime);

#endif // _DEBUG

	this->LateTick(fDeltaTime);

	this->ExecuteActorDestroy();

	this->ExecuteActorBeginPlay();

}

void UEngine::Terminate()
{
	bIsLoop = false;
}

void UEngine::DebugLog(string Text, int WarningLevel)
{
	DebugSubsystem->Log(Text, WarningLevel);
}

UWorld* UEngine::GetWorld() const
{
	return ActiveWorld.get();
}

UGameInstance* UEngine::GetGameInstance() const
{
	return ActiveGameInstance.get();
}

void UEngine::WorldTick(float fDeltaTime)
{
	ActiveWorld->ExecuteWorldSubsystemTick(fDeltaTime);

	ActiveWorld->ExecuteLevelTick(fDeltaTime);

	ActiveWorld->ExecuteActorTick(fDeltaTime);

	ActiveWorld->ElapsedTime += fDeltaTime;
}

void UEngine::LateTick(float fDeltaTime)
{
	ActiveWorld->ExecuteActorLateTick(fDeltaTime);
}

void UEngine::ExecuteNewWorldIfExists()
{
	if (WorldToOpen.size() > 0)
	{
		GEngine->ActiveWorld = WorldToOpen[WorldToOpen.size() - 1];
		GEngine->ActiveWorld->LateInit();
	}

	WorldToOpen.clear();
}

void UEngine::ExecuteActorDestroy()
{
	ActiveWorld->ExecuteActorDestroy();
}

void UEngine::ExecuteActorBeginPlay()
{
	ActiveWorld->ExecuteActorBeginPlay();
}

UEngine* GEngine = nullptr;
