#pragma once
#include "UObject/Object.h"

class UWorld;

class UWorldSubsystem : public UObject
{
public:
	virtual void Tick(float fDeltaTime) = 0;

	virtual void LateInit() = 0;

public:
	void SetWorld(UWorld* pWorld);

protected:
	UWorld* World;
};

