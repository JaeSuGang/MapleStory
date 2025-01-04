#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_TestActor : public AActor
{
public:
	BP_TestActor();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

};

