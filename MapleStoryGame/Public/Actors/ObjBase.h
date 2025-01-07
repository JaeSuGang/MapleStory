#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class AObjBase : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	AObjBase();

	virtual void BeginPlay();

	virtual void Tick(float fDeltaTime);

protected:
	URenderComponent* RenderComponent;
};

