#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_LucidIntro : public AActor
{
	typedef AActor Super;

public:
	BP_LucidIntro();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

};

