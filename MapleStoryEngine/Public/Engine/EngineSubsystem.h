#pragma once
#include "EngineDefine.h"
#include "UObject/Object.h"

class UEngine;

class UEngineSubsystem : public UObject
{
public:
	virtual void Tick(float fDeltaTime) = 0;

	virtual void LateInit() = 0;

public:
	void SetEngine(UEngine* pEngine);

protected:
	UEngine* Engine;
};

