#pragma once
#include "UObject/Object.h"

class AActor;

class UActorComponent : public UObject
{
public:

protected:
	AActor* Owner;
};

