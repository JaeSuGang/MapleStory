#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_TestSkill : public AActor
{
	typedef AActor Super;

public:
	BP_TestSkill();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

};

