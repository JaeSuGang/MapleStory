#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class AActor;

class ULevel : public UObject
{
	friend class UWorld;

public:
	/* �����ڿ� �������̵� */
	ENGINE_API ULevel();

protected:
	vector<shared_ptr<AActor>> Actors;
	vector<AActor*> ActorsToDestroy;
};

