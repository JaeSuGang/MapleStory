#pragma once
#include "Actor/Actor.h"
#include "Actors/Skills/SkillBase.h"

class URenderComponent;

class BP_TestSkill : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_TestSkill();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

};

