#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_FairyTurn_Range : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_FairyTurn_Range();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	void InitAttributes() override;

	void InitTexture() override;

};

