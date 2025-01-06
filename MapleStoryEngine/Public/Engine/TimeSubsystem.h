#pragma once
#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"

class UTimeSubsystem : public UEngineSubsystem
{
public:
	/* �����ڿ� �������̵� */
	UTimeSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API void TogglePause();

	ENGINE_API float GetFPS() const;

	ENGINE_API float GetDeltaTime() const;

	void SetDeltaTime(float fDeltaTime);

	void SetLastTimePointTime();

	float CalculateDeltaTime();

private:
	std::chrono::high_resolution_clock::time_point LastTimePoint;

	float DeltaTime;

	bool IsPaused;
};
