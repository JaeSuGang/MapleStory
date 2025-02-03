#pragma once
#include "Levels/MapBase.h"

class BP_LucidHPWidget;
class BP_LucidFlower;
class BP_LucidBoss_0;

class ULachelnDreamForest : public UMapBase
{
	typedef UMapBase Super;

public:
	ULachelnDreamForest();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

protected:
	void CheckGolemSpawn(float _fDeltaTime);

protected:
	BP_LucidHPWidget* BossHPWidget;
	weak_ptr<BP_LucidFlower> Flower;
	weak_ptr<BP_LucidBoss_0> LucidPhase1;
	float GolemSpawnTimer;
};

