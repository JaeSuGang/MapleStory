#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class AActor;

class ULevel : public UObject
{
	friend class UWorld;

protected:
	vector<shared_ptr<AActor>> Actors;
};

