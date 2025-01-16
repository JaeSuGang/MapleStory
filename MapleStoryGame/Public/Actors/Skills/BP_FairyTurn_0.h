#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_FairyTurn_0 : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_FairyTurn_0();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;
};

