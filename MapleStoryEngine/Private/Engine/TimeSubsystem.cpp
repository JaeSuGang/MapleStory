#include "EnginePch.h"
#include "Engine/TimeSubsystem.h"

UTimeSubsystem::UTimeSubsystem()
{
	DeltaTime = 0.0f;
	LastTimePoint = std::chrono::high_resolution_clock::now();
}

void UTimeSubsystem::Tick(float fDeltaTime)
{

}

void UTimeSubsystem::LateInit()
{

}

void UTimeSubsystem::TogglePause()
{
	if (!IsPaused)
		IsPaused = true;
	else
		IsPaused = false;
}

float UTimeSubsystem::GetFPS() const
{
	return 1 / DeltaTime;
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
	std::chrono::duration<float> DeltaTime;
	DeltaTime = std::chrono::high_resolution_clock::now() - LastTimePoint;
	return DeltaTime.count();
}
