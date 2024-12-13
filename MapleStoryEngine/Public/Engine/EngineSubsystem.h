#pragma once
#include "EngineAPI.h"
#include "UObject/Object.h"

class UEngineSubsystem : public UObject
{
public:
	virtual void Tick(float fDeltaTime) = 0;
};

