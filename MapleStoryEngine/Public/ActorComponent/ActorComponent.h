#pragma once
#include "UObject/Object.h"

class AActor;

class UActorComponent : public UObject
{
public:
	virtual void TickComponent(float fDeltaTime) = 0;

	void SetOwner(AActor* pOwner);

protected:
	AActor* Owner;
};

