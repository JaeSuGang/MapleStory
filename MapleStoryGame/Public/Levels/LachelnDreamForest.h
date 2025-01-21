#pragma once
#include "Levels/MapBase.h"

class ULachelnDreamForest : public UMapBase
{
	typedef UMapBase Super;

public:
	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

};

