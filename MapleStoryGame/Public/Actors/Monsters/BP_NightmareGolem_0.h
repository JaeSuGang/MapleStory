#pragma once
#include "MobBase.h"

class BP_NightmareGolem_0 : public AMobBase
{
	typedef AMobBase Super;

public:
	BP_NightmareGolem_0();

	void BeginPlay() override;

	void InitAttributes() override;

	void InitPhysics() override;
};

