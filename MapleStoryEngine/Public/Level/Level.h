#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class AActor;

class ULevel : public UObject
{
public:
	vector<shared_ptr<AActor>>& GetActorContainer();

protected:
	vector<shared_ptr<AActor>> Actors;
};

