#pragma once
#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"

class UTimeSubsystem : public UEngineSubsystem
{
public:
	/* 생성자와 오버라이드 */
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
