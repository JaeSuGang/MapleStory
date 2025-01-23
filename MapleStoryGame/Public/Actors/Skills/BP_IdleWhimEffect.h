#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_IdleWhimEffect : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_IdleWhimEffect();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	void InitAttributes() override;

	void InitTexture() override;

	void InitAnimations() override;

protected:
	bool HasSpawndWhims;
};

