#pragma once
#include "EnginePch.h"
#include "Engine/Engine.h"
#include "EngineSubsystem.h"

class UDebugSubsystem : public UEngineSubsystem
{
public:
	/* Contructors and Overrides */
	void Tick(float fDeltaTime) override;


	/* Warning Level 0 : Normal White Log */
	/* Warning Level 1 : Orange Log */
	/* Warning Level 2 : Red Log */
	ENGINE_API void Log(string Text, int WarningLevel);

};

