#pragma once
#include "Actors/Skills/SkillBase.h"

class URenderComponent;

class BP_TestSkill2 : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_TestSkill2();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

};

