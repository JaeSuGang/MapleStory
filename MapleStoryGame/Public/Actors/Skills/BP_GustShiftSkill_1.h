#pragma once
#include "Actors/SkillBase.h"

class BP_GustShiftSkill_1 : public ASkillBase
{
public:
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
};
