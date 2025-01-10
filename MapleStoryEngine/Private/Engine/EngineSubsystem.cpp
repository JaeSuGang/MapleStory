#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"

void UEngineSubsystem::Tick(float fDeltaTime)
{

}

void UEngineSubsystem::LateInit()
{

}

void UEngineSubsystem::SetEngine(UEngine* pEngine)
{
	Engine = pEngine;
}
