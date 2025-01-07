#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_TestCube : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	BP_TestCube();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	URenderComponent* RenderComponent;

};

