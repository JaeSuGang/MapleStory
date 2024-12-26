#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class BP_TestActor : public AActor
{
public:
	BP_TestActor();

protected:
	URenderComponent* RenderComponent;
};

