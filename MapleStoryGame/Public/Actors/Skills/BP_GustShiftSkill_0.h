#pragma once
#include "Actors/SkillBase.h"

class BP_GustShiftSkill_0 : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_GustShiftSkill_0();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
};

