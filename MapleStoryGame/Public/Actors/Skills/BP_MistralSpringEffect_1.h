#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_MistralSpringEffect_1 : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_MistralSpringEffect_1();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

	void InitTexture() override;
	void InitAnimations() override;

};

