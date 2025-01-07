#pragma once
#include "MobBase.h"

class BP_OrangeMushroom : public AMobBase
{
	typedef AMobBase Super;

public:
	void BeginPlay() override;

	void Tick(float fDeltaTime) override;
};

