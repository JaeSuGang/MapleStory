#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_TestCube : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	BP_TestCube();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	URenderComponent* RenderComponent;

};

