#pragma once
#include "Actors/Skills/SkillBase.h"

class BP_HowlingGaleEffect : public ASkillBase
{
	typedef ASkillBase Super;

public:
	BP_HowlingGaleEffect();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

	void InitAttributes() override;
	void InitTexture() override;
	void InitAnimations() override;

protected:
	float SpawnBallTimer;
	bool HasSpawnedBall;
};

