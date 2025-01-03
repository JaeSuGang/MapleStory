#include "EnginePch.h"
#include "Engine/TimeSubsystem.h"

UTimeSubsystem::UTimeSubsystem()
{
	DeltaTime = 0;
	LastTimePoint = std::chrono::high_resolution_clock::now();
}

void UTimeSubsystem::Tick(float fDeltaTime)
{

}

void UTimeSubsystem::LateInit()
{

}

ENGINE_API void UTimeSubsystem::TogglePause()
{
	if (!IsPaused)
		IsPaused = true;
	else
		IsPaused = false;
}

float UTimeSubsystem::GetDeltaTime() const
{
	return DeltaTime;
}

void UTimeSubsystem::SetDeltaTime(float fDeltaTime)
{
	DeltaTime = fDeltaTime;
}

void UTimeSubsystem::SetLastTimePointTime()
{
	LastTimePoint = std::chrono::high_resolution_clock::now();
}

float UTimeSubsystem::CalculateDeltaTime()
{
	std::chrono::duration<float> fDeltaTime;
	fDeltaTime = std::chrono::high_resolution_clock::now() - LastTimePoint;
	return fDeltaTime.count();
}
