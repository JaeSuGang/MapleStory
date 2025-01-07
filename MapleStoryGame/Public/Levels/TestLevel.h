#pragma once
#include "Levels/MapBase.h"

class UTestLevel : public UMapBase
{
	typedef UMapBase Super;

public:
	void BeginPlay() override;

	void Tick(float fDeltaTime) override;
};

