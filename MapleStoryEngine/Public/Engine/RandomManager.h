#pragma once
#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"

class URandomManager : public UEngineSubsystem
{
public:
	URandomManager();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API float GenerateRandomFloatValue(float RangeA, float RangeB);

public:
	shared_ptr<std::random_device> RandomDevice;

	shared_ptr<std::mt19937_64> Gen;
};

