#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_MistralSpringEffect_0 : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_MistralSpringEffect_0();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

	void InitTexture() override;
	void InitAnimations() override;

};

