#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_GustShiftSkill_1 : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_GustShiftSkill_1();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
};
