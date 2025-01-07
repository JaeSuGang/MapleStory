#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class AObjBase : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	AObjBase();

	virtual void BeginPlay();

	virtual void Tick(float fDeltaTime);

protected:
	URenderComponent* RenderComponent;
};

