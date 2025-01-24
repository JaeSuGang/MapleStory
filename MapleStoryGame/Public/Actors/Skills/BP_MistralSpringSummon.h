#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_MistralSpringSummon : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_MistralSpringSummon();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

	void InitTexture() override;
	void InitAnimations() override;

};

