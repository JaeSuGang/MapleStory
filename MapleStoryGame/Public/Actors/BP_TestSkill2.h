#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_TestSkill2 : public AActor
{
	typedef AActor Super;

public:
	BP_TestSkill2();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

};

