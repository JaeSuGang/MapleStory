#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_MistralSpringScreen : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_MistralSpringScreen();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

	void InitTexture() override;
	void InitAnimations() override;

protected:
	bool HasSpawnedSpecialEffect;
};

